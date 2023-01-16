/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:28:08 by obibby            #+#    #+#             */
/*   Updated: 2023/01/15 12:47:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ray(t_cub3D *game, int x)
{
	game->ray.cameraX = 2 * x / (double)game->window_width - 1;
	game->ray.rayDirX = game->player.dirX + game->player.viewX
		* game->ray.cameraX;
	game->ray.rayDirY = game->player.dirY + game->player.viewY
		* game->ray.cameraX;
	game->ray.mapX = (int)game->player.posX;
	game->ray.mapY = (int)game->player.posY;
}

void	get_delta_dist(t_cub3D *game)
{
	if (!game->ray.rayDirY)
		game->ray.deltaDistY = 1e30;
	else
		game->ray.deltaDistY = ft_abs(1 / game->ray.rayDirY);
	if (!game->ray.rayDirX)
		game->ray.deltaDistX = 1e30;
	else
		game->ray.deltaDistX = ft_abs(1 / game->ray.rayDirX);
}

void	get_side_dist(t_cub3D *game)
{
	if (game->ray.rayDirX < 0)
	{
		game->ray.stepX = -1;
		game->ray.sideDistX = (game->player.posX - game->ray.mapX)
			* game->ray.deltaDistX;
	}
	else
	{
		game->ray.stepX = 1;
		game->ray.sideDistX = (game->ray.mapX + 1.0 - game->player.posX)
			* game->ray.deltaDistX;
	}
	if (game->ray.rayDirY < 0)
	{
		game->ray.stepY = -1;
		game->ray.sideDistY = (game->player.posY - game->ray.mapY)
			* game->ray.deltaDistY;
	}
	else
	{
		game->ray.stepY = 1;
		game->ray.sideDistY = (game->ray.mapY + 1.0 - game->player.posY)
			* game->ray.deltaDistY;
	}
}

void	get_hit(t_cub3D *game, int *side)
{
	int	hit;

	hit = 0;
	game->door_hit = 0;
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
		if (game->map_arr[game->ray.mapY][game->ray.mapX] == '1' ||
			(game->map_arr[game->ray.mapY][game->ray.mapX] == 'D'
			&& check_door(game, *side)))
			hit = 1;
	}
}

void	get_perp_wall_dist(t_cub3D *game, int side)
{
	if (!side)
		game->ray.perpWallDist = (game->ray.sideDistX
				- game->ray.deltaDistX);
	else
		game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);
}
