/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:28:08 by obibby            #+#    #+#             */
/*   Updated: 2023/01/14 22:32:04 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_perp_wall_dist(t_cub3D *game, int side)
{
	if (!side)
		game->ray.perpWallDist = (game->ray.sideDistX
				- game->ray.deltaDistX);
	else
		game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);
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
