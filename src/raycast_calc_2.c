/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:49:36 by obibby            #+#    #+#             */
/*   Updated: 2023/01/15 18:17:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_draw_coords(t_cub3D *game)
{
	game->ray.lineHeight = game->window_height / game->ray.perpWallDist;
	game->ray.drawStart = -game->ray.lineHeight / 2 + game->window_height / 2;
	if (game->ray.drawStart < 0)
		game->ray.drawStart = 0;
	game->ray.drawEnd = game->ray.lineHeight / 2 + game->window_height / 2;
	if (game->ray.drawEnd >= game->window_height)
		game->ray.drawEnd = game->window_height - 1;
}

void	get_tex_pos(t_cub3D *game, int side)
{
	double	wallx;

	if (!side)
		wallx = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
	else
		wallx = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
	wallx -= floor(wallx);
	game->ray.texX = (int)(wallx * (double)RESOLUTION);
	if (side == 0 && game->ray.rayDirX > 0)
		game->ray.texX = RESOLUTION - game->ray.texX - 1;
	else if (side == 1 && game->ray.rayDirY < 0)
		game->ray.texX = RESOLUTION - game->ray.texX - 1;
	game->ray.step = 1.0 * RESOLUTION / game->ray.lineHeight;
	game->ray.tex_pos = (game->ray.drawStart - game->window_height
			/ 2 + game->ray.lineHeight / 2) * game->ray.step;
}

void	put_compass(t_cub3D *game, int x, int y)
{
	my_mlx_pixel_put(&game->img, x, y, game->compass);
	if (game->ray.rayDirY < -0.9995
		&& game->ray.rayDirY > -1.0005)
	{
		game->ray.north_x = x;
		game->ray.north_y = y;
	}
	else if (game->ray.rayDirX > 0.9995
		&& game->ray.rayDirX < 1.0005)
	{
		game->ray.east_x = x;
		game->ray.east_y = y;
	}
	else if (game->ray.rayDirY > 0.9995
		&& game->ray.rayDirY < 1.0005)
	{
		game->ray.south_x = x;
		game->ray.south_y = y;
	}
	else if (game->ray.rayDirX < -0.9995
		&& game->ray.rayDirX > -1.0005)
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
