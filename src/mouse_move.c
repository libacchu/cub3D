/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:08 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/19 09:48:27 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_left(t_cub3D *game, int x_dif)
{
	double	old_x;

	old_x = 0;
	while (x_dif++ < 0)
	{
		old_x = game->player.dir_x;
		game->player.dir_x = old_x * cos(-MOUSE_SPEED) \
			- game->player.dir_y * sin(-MOUSE_SPEED);
		game->player.dir_y = old_x * sin(-MOUSE_SPEED) \
			+ game->player.dir_y * cos(-MOUSE_SPEED);
		old_x = game->player.view_x;
		game->player.view_x = old_x * cos(-MOUSE_SPEED) \
			- game->player.view_y * sin(-MOUSE_SPEED);
		game->player.view_y = old_x * sin(-MOUSE_SPEED) \
			+ game->player.view_y * cos(-MOUSE_SPEED);
	}
}

void	rotate_right(t_cub3D *game, int x_dif)
{
	double	old_x;

	old_x = 0;
	while (x_dif-- > 0)
	{
		old_x = game->player.dir_x;
		game->player.dir_x = old_x * cos(MOUSE_SPEED) \
			- game->player.dir_y * sin(MOUSE_SPEED);
		game->player.dir_y = old_x * sin(MOUSE_SPEED) \
			+ game->player.dir_y * cos(MOUSE_SPEED);
		old_x = game->player.view_x;
		game->player.view_x = old_x * cos(MOUSE_SPEED) \
			- game->player.view_y * sin(MOUSE_SPEED);
		game->player.view_y = old_x * sin(MOUSE_SPEED) \
			+ game->player.view_y * cos(MOUSE_SPEED);
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
