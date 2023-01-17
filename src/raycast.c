/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:29:47 by obibby            #+#    #+#             */
/*   Updated: 2023/01/17 10:42:16 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_minimap(t_cub3D *game)
{
	int	x;
	int	side;

	if (!game->once)
	{
		mlx_clear_window(game->mlx, game->window);
		game->once = 1;
	}
	refresh_minimap(game);
	x = -1;
	while (++x < game->minimap_size_x)
	{
		init_ray(game, x);
		get_delta_dist(game);
		get_side_dist(game);
		get_hit(game, &side);
		line_algo(game, game->player.posX * 34, game->player.posY * 34);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->minimap.img,
		game->half_width - 10 - game->player.posX * 34, game->half_height
		- 10 - game->player.posY * 34);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap_player.img,
		game->half_width - 8, game->half_height - 10);
}

void	sort_sprites(int *sprite_order, int *sprite_distance, int total_sprites)
{
	int	x;
	int	y;

	x = 0;
	while (x < total_sprites)
	{
		y = x + 1;
		while (y < total_sprites)
		{
			if (sprite_distance[y] > sprite_distance[x])
				ft_swap(&sprite_distance[x], &sprite_distance[y], &sprite_order[x], &sprite_order[y]);
			y++;
		}
		x++;
	}
}

int	do_stuff_to_sprites(t_cub3D *game)
{
	t_sprite *sprite;
	int			*sprite_order;
	int			*sprite_distance;
	int			i;
	
	sprite_order = ft_calloc(game->sprite_total, sizeof(int));
	if (!sprite_order)
		return (err_message("Memory allocation failed."));
	sprite_distance = ft_calloc(game->sprite_total, sizeof(int));
	if (!sprite_distance)
		return (err_message("Memory allocation failed."));	
	sprite = game->sprite_list;
	i = 0;
	while (sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((game->player.posX - sprite->x) * (game->player.posX - sprite->x) + (game->player.posY - sprite->y) * (game->player.posY - sprite->y));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, game->sprite_total);
	i = -1;
	while (++i < game->sprite_total)
	{
		double	sprite_x;
		double	sprite_y;
		double	inv_det;
		double	trans_x;
		double	trans_y;
		int		s_screen_x;
		int		s_screen_y;

		sprite_x = game->sprite_list[sprite_order[i]].x - game->player.posX;
		sprite_y = game->sprite_list[sprite_order[i]].y - game->player.posY;
		inv_det = 1.0 / (game->player.viewX * game->player.dirY - game->player.dirX * game->player.viewY);
		trans_x = inv_det * (game->player.dirY * sprite_x - game->player.dirX * sprite_y);
		trans_y = inv_det * (-game->player.viewY * sprite_x + game->player.viewX * sprite_y);
		s_screen_x = (int)(game->half_width * (1 + trans_x / trans_y));
	}

	// //after sorting the sprites, do the projection and draw them
    // for(int i = 0; i < numSprites; i++)
    // {
    //   //translate sprite position to relative to camera
    //   double spriteX = sprite[spriteOrder[i]].x - posX;
    //   double spriteY = sprite[spriteOrder[i]].y - posY;

    //   //transform sprite with the inverse camera matrix
    //   // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    //   // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    //   // [ planeY   dirY ]                                          [ -planeY  planeX ]

    //   double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

    //   double transformX = invDet * (dirY * spriteX - dirX * spriteY);
    //   double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

    //   int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

    //   //calculate height of the sprite on screen
    //   int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
    //   //calculate lowest and highest pixel to fill in current stripe
    //   int drawStartY = -spriteHeight / 2 + h / 2;
    //   if(drawStartY < 0) drawStartY = 0;
    //   int drawEndY = spriteHeight / 2 + h / 2;
    //   if(drawEndY >= h) drawEndY = h - 1;

    //   //calculate width of the sprite
    //   int spriteWidth = abs( int (h / (transformY)));
    //   int drawStartX = -spriteWidth / 2 + spriteScreenX;
    //   if(drawStartX < 0) drawStartX = 0;
    //   int drawEndX = spriteWidth / 2 + spriteScreenX;
    //   if(drawEndX >= w) drawEndX = w - 1;

    //   //loop through every vertical stripe of the sprite on screen
    //   for(int stripe = drawStartX; stripe < drawEndX; stripe++)
    //   {
    //     int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
    //     //the conditions in the if are:
    //     //1) it's in front of camera plane so you don't see things behind you
    //     //2) it's on the screen (left)
    //     //3) it's on the screen (right)
    //     //4) ZBuffer, with perpendicular distance
    //     if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
    //     for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
    //     {
    //       int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
    //       int texY = ((d * texHeight) / spriteHeight) / 256;
    //       Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
    //       if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
    //     }
    //   }
}

int	raycast(t_cub3D *game)
{
	int		x;
	int		side;
	t_image	*img;

	x = -1;
	if (!game->tab)
	{
		init_compass(game);
		while (++x < game->window_width)
		{
			init_ray(game, x);
			get_delta_dist(game);
			get_side_dist(game);
			get_hit(game, &side);
			get_perp_wall_dist(game, side);
			get_draw_coords(game);
			get_tex_pos(game, side);
			img = set_image_ptr(game, side);
			draw_to_image(game, x, img);
			game->ray.zbuffer[x] = game->ray.perpWallDist;
		}
		do_stuff_to_sprites(game);
		put_images_to_window(game);
	}
	else
		put_minimap(game);
	return (0);
}
