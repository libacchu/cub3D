/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:44:41 by obibby            #+#    #+#             */
/*   Updated: 2023/01/16 18:07:09 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_images_to_window(t_cub3D *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	if (game->ray.north_x)
		mlx_put_image_to_window(game->mlx, game->window,
			game->north_compass.img, game->ray.north_x - 6,
			game->ray.north_y - 12);
	if (game->ray.east_x)
		mlx_put_image_to_window(game->mlx, game->window,
			game->east_compass.img, game->ray.east_x - 6,
			game->ray.east_y - 14);
	if (game->ray.south_x)
		mlx_put_image_to_window(game->mlx, game->window,
			game->south_compass.img, game->ray.south_x - 6,
			game->ray.south_y - 12);
	if (game->ray.west_x)
		mlx_put_image_to_window(game->mlx, game->window,
			game->west_compass.img, game->ray.west_x - 6,
			game->ray.west_y - 11);
}

void	get_pixel_colour(t_cub3D *game, t_image *img, int x, int y)
{
	int	colour;

	game->ray.texY = (int)game->ray.tex_pos & (RESOLUTION - 1);
	game->ray.tex_pos += game->ray.step;
	colour = *(int *)(img->addr + game->ray.texY % RESOLUTION * img->line_size
			+ game->ray.texX % RESOLUTION * (img->bpp / 8));
	my_mlx_pixel_put(&game->img, x, y, colour);
}

int	check_sprite_hit(t_cub3D *game, int x, int y)
{
	t_sprite	*sprite;

	sprite = game->sprite_list;
	while(sprite)
	{
		if (sprite->sprite_hit)
		{
			if (check_colour_pix(&game->sprite[sprite->sp_anime], ((64 * sprite->sp_img) + (x / 8)), (y / 8)))
				return (1);
		}
		sprite = sprite->next;
	}
	return (0);
}

void	draw_to_image(t_cub3D *game, int x, t_image *img)
{
	int	y;

	y = -1;
	while (++y < game->window_height)
	{
		if (y > game->y_down_limit / 3 && y < game->y_down_limit / 2
			&& x > game->x_left_limit && x < game->x_right_limit)
			put_compass(game, x, y);
		else if (y < game->ray.drawStart)
			my_mlx_pixel_put(&game->img, x, y, game->ceiling);
		else if (y > game->ray.drawEnd)
			my_mlx_pixel_put(&game->img, x, y, game->floor);
		else if (check_sprite_hit(game, x, y))
			get_sprite_colour(game, x, y);
		else if (game->door_hit && ((int)game->ray.tex_pos
				& (RESOLUTION - 1)) > 25)
			get_door_colour(game, &game->door, x, y);
		else
			get_pixel_colour(game, img, x, y);
	}
}

t_image	*set_image_ptr(t_cub3D *game, int side)
{
	t_image	*img;

	if (side == 0 && game->ray.rayDirX > 0)
		img = &game->east_wall;
	else if (side == 0)
		img = &game->west_wall;
	else if (side == 1 && game->ray.rayDirY > 0)
		img = &game->south_wall;
	else
		img = &game->north_wall;
	return (img);
}

void	pixel_put_image(t_cub3D *game, t_image *img, int x, int y)
{
	int	j;
	int	k;
	int	colour;

	j = -1;
	while (++j < 34)
	{
		k = -1;
		while (++k < 34)
		{
			colour = *(int *)(img->addr + (j * img->line_size
						+ k * (img->bpp / 8)));
			my_mlx_pixel_put(&game->minimap, x * 34 + k + 10,
				y * 34 + j + 10, colour);
		}
	}
}
