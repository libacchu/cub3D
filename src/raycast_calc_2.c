/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:49:36 by obibby            #+#    #+#             */
/*   Updated: 2023/01/14 22:50:08 by obibby           ###   ########.fr       */
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

void	get_hit(t_cub3D *game, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (game->ray.sideDistX < game->ray.sideDistY)
		{
			game->ray.sideDistX += game->ray.deltaDistX;
			game->ray.mapX += game->ray.stepX;
			*side = 0;
		}
		else
		{
			game->ray.sideDistY += game->ray.deltaDistY;
			game->ray.mapY += game->ray.stepY;
			*side = 1;
		}
		if (game->map_arr[game->ray.mapY][game->ray.mapX] == '1')
			hit = 1;
	}
}

void	put_compass(t_cub3D *game, int x, int y)
{
	my_mlx_pixel_put(&game->img, x, y, game->compass);
	if (game->ray.rayDirY < -0.999
		&& game->ray.rayDirY > -1.001)
	{
		game->ray.north_x = x;
		game->ray.north_y = y;
	}
	else if (game->ray.rayDirX > 0.999
		&& game->ray.rayDirX < 1.001)
	{
		game->ray.east_x = x;
		game->ray.east_y = y;
	}
	else if (game->ray.rayDirY > 0.999
		&& game->ray.rayDirY < 1.001)
	{
		game->ray.south_x = x;
		game->ray.south_y = y;
	}
	else if (game->ray.rayDirX < -0.999
		&& game->ray.rayDirX > -1.001)
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
