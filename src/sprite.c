/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:42:39 by obibby            #+#    #+#             */
/*   Updated: 2023/01/16 18:36:42 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	add_sprite(t_cub3D *game, int x, int y)
{
	t_sprite	*new_sprite;
	t_sprite	*sprite;

	new_sprite = ft_calloc(1, sizeof(t_sprite));
	if (!new_sprite)
		return (err_message("Failed to allocate memory.\n"));
	new_sprite->x = x;
	new_sprite->y = y;
	new_sprite->sp_img = 5;
	new_sprite->sp_anime = 0;
	new_sprite->sprite_hit = 0;
	new_sprite->sprite_active = 1;
	new_sprite->next = NULL;
	if (!game->sprite_list)
		game->sprite_list = new_sprite;
	else
	{
		sprite = game->sprite_list;
		while (sprite->next)
			sprite = sprite->next;
		sprite->next = new_sprite;
	}
	game->sprite_total++;
	return (0);
}

void	assign_sprite(t_cub3D *game)
{
	int	x;
	int	y;

	
	game->sprite = ft_calloc(4, sizeof(t_image));
	game->sprite[0].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-appears.xpm", &x, &y);
	game->sprite[0].addr = mlx_get_data_addr(game->sprite[0].img,
			&game->sprite[0].bpp, &game->sprite[0].line_size,
			&game->sprite[0].endian);
	game->sprite[1].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-idle.xpm", &x, &y);
	game->sprite[1].addr = mlx_get_data_addr(game->sprite[1].img,
			&game->sprite[1].bpp, &game->sprite[1].line_size,
			&game->sprite[1].endian);
	game->sprite[2].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-shriek.xpm", &x, &y);
	game->sprite[2].addr = mlx_get_data_addr(game->sprite[2].img,
			&game->sprite[2].bpp, &game->sprite[2].line_size,
			&game->sprite[2].endian);
	game->sprite[3].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-vanish.xpm", &x, &y);
	game->sprite[3].addr = mlx_get_data_addr(game->sprite[3].img,
			&game->sprite[3].bpp, &game->sprite[3].line_size,
			&game->sprite[3].endian);
	game->ray.zbuffer = ft_calloc(game->window_width, sizeof(double));
}

int	check_colour_pix(t_image *data, int x, int y)
{
	int		i;
	int 	color;

	color = *(unsigned int *)(data->addr + (y * data->line_size + x * (data->bpp / 8)));

	i = -1;
	// while (++i < 3)
	// {
		if(color != 0x06FF00)
			return (1);
	// }
	return (0);
}

int	check_sprite(t_cub3D *game, int side)
{
	t_sprite	*sprite;
	int y;
	
	if (side == 1)
		return (0);
	sprite = game->sprite_list;
	while (sprite)
	{
		if (sprite->x == game->ray.mapX && sprite->y == game->ray.mapY)
		{
			get_perp_wall_dist(game, side);
			get_draw_coords(game);
			get_tex_pos(game, side);
			if (sprite->sprite_active)
			{
				y = -1;
				while (++y < 64)
				{
					if (check_colour_pix(&game->sprite[sprite->sp_anime], ((64 * sprite->sp_img) + (game->ray.texX / 8)), y))
					{
						sprite->sprite_hit = 1;
						return (1);
					}
				}
			}
			break ;
		}
		sprite = sprite->next;
	}
	return (0);
}

void	get_sprite_colour(t_cub3D *game, int x, int y)
{
	int	colour;
	t_sprite	*sprite;
	
	sprite = game->sprite_list;
	while (sprite)
	{
		if(sprite->sprite_hit)
		{
			
			game->ray.texY = (int)(game->ray.tex_pos / 8) & (64 - 1);
			game->ray.tex_pos += game->ray.step;
			
			colour = *(int *)(game->sprite[sprite->sp_anime].addr + game->ray.texY % 64 * game->sprite[sprite->sp_anime].line_size
					+ (((game->ray.texX / 8) % 64) + 64 * sprite->sp_img) * (game->sprite[sprite->sp_anime].bpp / 8));

		
			if(colour != 0X06FF00)
				my_mlx_pixel_put(&game->img, x, y, colour);
		}
		sprite = sprite->next;
	}
	
}

// void	find_door(t_cub3D *game)
// {
// 	if (game->player.dirX > 0.5 && game->map_arr[(int)game->player.posY]
// 		[(int)game->player.posX + 1] == 'D')
// 		open_door(game, game->player.posX + 1, game->player.posY);
// 	else if (game->player.dirX < -0.5 && game->map_arr[(int)game->player.posY]
// 		[(int)game->player.posX - 1] == 'D')
// 		open_door(game, game->player.posX - 1, game->player.posY);
// 	else if (game->player.dirY > 0.5 && game->map_arr
// 		[(int)game->player.posY + 1][(int)game->player.posX] == 'D')
// 		open_door(game, game->player.posX, game->player.posY + 1);
// 	else if (game->player.dirY < -0.5 && game->map_arr
// 		[(int)game->player.posY - 1][(int)game->player.posX] == 'D')
// 		open_door(game, game->player.posX, game->player.posY - 1);
// }
