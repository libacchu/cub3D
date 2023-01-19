/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:11:01 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/19 09:39:21 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
/* 
	- Keys
		- left/right arrow: allow you to look left and right in the maze.
		- W A S D:  move the point of view through the maze
		- ESC: close the window and quit the program cleanly
		- red cross: close the window and quit the program cleanly.
 */

void	toggle_shift(t_cub3D *game)
{
	if (game->shift)
		game->shift = 0;
	else
		game->shift = 1;
}

void	toggle_tab(t_cub3D *game)
{
	if (game->tab)
	{
		game->tab = 0;
		game->once = 0;
	}
	else
		game->tab = 1;
}

int	ft_key(int keycode, t_cub3D *game)
{
	if (keycode == KEY_ESC)
		ft_exit(NULL, game);
	else if (keycode == KEY_W)
		move_player(game, game->player.dir_y, game->player.dir_x, 1);
	else if (keycode == KEY_A)
		move_player(game, game->player.view_y, game->player.view_x, -1);
	else if (keycode == KEY_S)
		move_player(game, game->player.dir_y, game->player.dir_x, -1);
	else if (keycode == KEY_D)
		move_player(game, game->player.view_y, game->player.view_x, 1);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -1);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, 1);
	else if (keycode == KEY_E)
		find_door(game);
	else if (keycode == KEY_TAB)
		toggle_tab(game);
	else if (keycode == KEY_SHIFT)
		toggle_shift(game);
	return (0);
}

int	ft_mouse(t_cub3D *game)
{
	ft_exit(NULL, game);
	return (0);
}
