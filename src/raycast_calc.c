/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:28:08 by obibby            #+#    #+#             */
/*   Updated: 2023/01/23 11:01:16 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ray(t_cub3D *game, int x)
{
	game->ray.camera_x = 2 * x / (double)game->window_width - 1;
	game->ray.ray_dir_x = game->player.dir_x + game->player.view_x
		* game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y + game->player.view_y
		* game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
}

void	get_delta_dist(t_cub3D *game)
{
	if (!game->ray.ray_dir_y)
		game->ray.delta_dist_y = 1e30;
	else
		game->ray.delta_dist_y = ft_abs(1 / game->ray.ray_dir_y);
	if (!game->ray.ray_dir_x)
		game->ray.delta_dist_x = 1e30;
	else
		game->ray.delta_dist_x = ft_abs(1 / game->ray.ray_dir_x);
}

void	get_side_dist(t_cub3D *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

int	get_hit(t_cub3D *game)
{
	int	hit;
	int	side;

	hit = 0;
	game->door_hit = 0;
	while (!hit)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			side = 1;
		}
		if (game->map_arr[game->ray.map_y][game->ray.map_x] == '1' ||
			(game->map_arr[game->ray.map_y][game->ray.map_x] == 'D'
			&& check_door(game, side)))
			hit = 1;
	}
	return (side);
}

void	get_perp_wall_dist(t_cub3D *game, int side)
{
	if (!side)
		game->ray.perp_wall_dist = (game->ray.side_dist_x
				- game->ray.delta_dist_x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist_y - \
			game->ray.delta_dist_y);
}
