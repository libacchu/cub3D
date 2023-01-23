/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:55:22 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/23 11:10:04 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	assign_view(t_cub3D *game, double view_x, double view_y)
{
	game->player.view_x = view_x;
	game->player.view_y = view_y;
}

void	assign_dir(t_cub3D *game, double dir_x, double dir_y)
{
	game->player.dir_x = dir_x;
	game->player.dir_y = dir_y;
}

void	player_start_direction(int x, int y, t_cub3D *game)
{
	game->player.direct = game->map_arr[y][x];
	game->player.pos_x = 0.5 + x;
	game->player.pos_y = 0.5 + y;
	if (game->map_arr[y][x] == 'N')
	{
		assign_dir(game, 0, -1);
		assign_view(game, 0.60, 0);
	}
	if (game->map_arr[y][x] == 'E')
	{
		assign_dir(game, 1, 0);
		assign_view(game, 0, 0.60);
	}
	if (game->map_arr[y][x] == 'S')
	{
		assign_dir(game, 0, 1);
		assign_view(game, -0.60, 0);
	}
	if (game->map_arr[y][x] == 'W')
	{
		assign_dir(game, -1, 0);
		assign_view(game, 0, -0.60);
	}
}
