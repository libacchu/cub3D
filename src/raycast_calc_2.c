/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:49:36 by obibby            #+#    #+#             */
/*   Updated: 2023/01/23 16:56:12 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_draw_coords(t_cub3D *game)
{
	game->ray.line_height = game->window_height / game->ray.perp_wall_dist;
	game->ray.draw_start = -game->ray.line_height * 0.5 + game->half_height;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height * 0.5 + game->half_height;
	if (game->ray.draw_end >= game->window_height)
		game->ray.draw_end = game->window_height - 1;
}

void	get_tex_pos(t_cub3D *game, int side)
{
	double	wallx;

	if (!side)
		wallx = game->player.pos_y + \
			game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		wallx = game->player.pos_x + \
			game->ray.perp_wall_dist * game->ray.ray_dir_x;
	wallx -= floor(wallx);
	game->ray.tex_x = (int)(wallx * (double)RESOLUTION);
	if (side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = RESOLUTION - game->ray.tex_x - 1;
	else if (side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = RESOLUTION - game->ray.tex_x - 1;
	game->ray.step = 1.0 * RESOLUTION / game->ray.line_height;
	game->ray.tex_pos = (game->ray.draw_start - game->half_height
			+ game->ray.line_height * 0.5) * game->ray.step;
}

void	put_compass(t_cub3D *game, int x, int y)
{
	my_mlx_pixel_put(&game->img, x, y, game->compass);
	if (game->ray.ray_dir_y < -0.9995
		&& game->ray.ray_dir_y > -1.0005)
	{
		game->ray.north_x = x;
		game->ray.north_y = y;
	}
	else if (game->ray.ray_dir_x > 0.9995
		&& game->ray.ray_dir_x < 1.0005)
	{
		game->ray.east_x = x;
		game->ray.east_y = y;
	}
	else if (game->ray.ray_dir_y > 0.9995
		&& game->ray.ray_dir_y < 1.0005)
	{
		game->ray.south_x = x;
		game->ray.south_y = y;
	}
	else if (game->ray.ray_dir_x < -0.9995
		&& game->ray.ray_dir_x > -1.0005)
	{
		game->ray.west_x = x;
		game->ray.west_y = y;
	}
}

void	init_compass(t_cub3D *game)
{
	game->ray.north_x = 0;
	game->ray.north_y = 0;
	game->ray.east_x = 0;
	game->ray.east_y = 0;
	game->ray.south_x = 0;
	game->ray.south_y = 0;
	game->ray.west_x = 0;
	game->ray.west_y = 0;
}
