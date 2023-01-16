/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:08 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/15 01:31:34 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_left(t_cub3D *game, int x_dif)
{
	double	old_x;

	old_x = 0;
	while (x_dif++ < 0)
	{
		old_x = game->player.dirX;
		game->player.dirX = old_x * cos(-MOUSE_SPEED) \
			- game->player.dirY * sin(-MOUSE_SPEED);
		game->player.dirY = old_x * sin(-MOUSE_SPEED) \
			+ game->player.dirY * cos(-MOUSE_SPEED);
		old_x = game->player.viewX;
		game->player.viewX = old_x * cos(-MOUSE_SPEED) \
			- game->player.viewY * sin(-MOUSE_SPEED);
		game->player.viewY = old_x * sin(-MOUSE_SPEED) \
			+ game->player.viewY * cos(-MOUSE_SPEED);
	}
}

void	rotate_right(t_cub3D *game, int x_dif)
{
	double	old_x;

	old_x = 0;
	while (x_dif-- > 0)
	{
		old_x = game->player.dirX;
		game->player.dirX = old_x * cos(MOUSE_SPEED) \
			- game->player.dirY * sin(MOUSE_SPEED);
		game->player.dirY = old_x * sin(MOUSE_SPEED) \
			+ game->player.dirY * cos(MOUSE_SPEED);
		old_x = game->player.viewX;
		game->player.viewX = old_x * cos(MOUSE_SPEED) \
			- game->player.viewY * sin(MOUSE_SPEED);
		game->player.viewY = old_x * sin(MOUSE_SPEED) \
			+ game->player.viewY * cos(MOUSE_SPEED);
	}
}

int	mouse_move(int x, int y, t_cub3D *game)
{
	int	x_dif;

	mlx_mouse_get_pos(game->mlx, game->window, &x, &y);
	x_dif = x - game->mouse_prev_x;
	game->mouse_prev_x = x;
	game->mouse_prev_y = y;
	if (x_dif < 0)
		rotate_left(game, x_dif);
	else if (x_dif > 0)
		rotate_right(game, x_dif);
	if (game->mouse_prev_x > game->x_right_limit || \
		game->mouse_prev_x < game->x_left_limit || \
		game->mouse_prev_y > game->y_up_limit || \
		game->mouse_prev_y < game->y_down_limit)
	{
		game->mouse_prev_x = game->half_width;
		game->mouse_prev_y = game->half_height;
		mlx_mouse_move(game->mlx, game->window, \
			game->half_width, game->half_height);
	}
	return (0);
}