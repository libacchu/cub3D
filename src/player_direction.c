/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:55:22 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/14 14:56:02 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	assign_view(t_cub3D *game, double viewX, double viewY)
{
	game->player.viewX = viewX;
	game->player.viewY = viewY;
}

void	assign_dir(t_cub3D *game, double dirX, double dirY)
{
	game->player.dirX = dirX;
	game->player.dirY = dirY;
}

void	player_start_direction(int x, int y, t_cub3D *game)
{
	game->player.direct = game->map_arr[y][x];
	game->player.posX = 0.5 + x;
	game->player.posY = 0.5 + y;
	if (game->map_arr[y][x] == 'N')
	{
		assign_dir(game, 0, -1);
		assign_view(game, 0.90, 0);
	}
	if (game->map_arr[y][x] == 'E')
	{
		assign_dir(game, 1, 0);
		assign_view(game, 0, 0.90);
	}
	if (game->map_arr[y][x] == 'S')
	{
		assign_dir(game, 0, 1);
		assign_view(game, -0.90, 0);
	}
	if (game->map_arr[y][x] == 'W')
	{
		assign_dir(game, -1, 0);
		assign_view(game, 0, -0.90);
	}
}
