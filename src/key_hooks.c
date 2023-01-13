/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:11:01 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/13 16:44:32 by libacchu         ###   ########.fr       */
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

int	ft_key(int keycode, t_cub3D *game)
{
	if (keycode == KEY_ESC)
		ft_exit(NULL, game);
	if (keycode == KEY_W)
	{
		game->player.posY += game->player.dirY;
		game->player.posX += game->player.dirX;
	}
	if (keycode == KEY_A)
	{
		game->player.posY -= game->player.viewY;
		game->player.posX -= game->player.viewX;
	}
	if (keycode == KEY_S)
	{
		game->player.posY -= game->player.dirY;
		game->player.posX -= game->player.dirX;
	}
	if (keycode == KEY_D)
	{
		game->player.posY += game->player.viewY;
		game->player.posX += game->player.viewX;
	}
	if (keycode == KEY_LEFT)
	{
		double	old_X;
		old_X = game->player.dirX;
		game->player.dirX = old_X * cos(-ROTATE_SPEED) - game->player.dirY * sin(-ROTATE_SPEED);
		game->player.dirY = old_X * sin(-ROTATE_SPEED) + game->player.dirY * cos(-ROTATE_SPEED);
		old_X = game->player.viewX;
		game->player.viewX = old_X * cos(-ROTATE_SPEED) - game->player.viewY * sin(-ROTATE_SPEED);
		game->player.viewY = old_X * sin(-ROTATE_SPEED) + game->player.viewY * cos(-ROTATE_SPEED);
	}
		//rotation matrix
	if (keycode == KEY_RIGHT)
	{
		double	old_X;
		old_X = game->player.dirX;
		game->player.dirX = old_X * cos(ROTATE_SPEED) - game->player.dirY * sin(ROTATE_SPEED);
		game->player.dirY = old_X * sin(ROTATE_SPEED) + game->player.dirY * cos(ROTATE_SPEED);
		old_X = game->player.viewX;
		game->player.viewX = old_X * cos(ROTATE_SPEED) - game->player.viewY * sin(ROTATE_SPEED);
		game->player.viewY = old_X * sin(ROTATE_SPEED) + game->player.viewY * cos(ROTATE_SPEED);
	}
	if (keycode == KEY_TAB)
	{
		if (game->tab)
			game->tab = 0;
		else
			game->tab = 1;
	}
	return (0);
}

int	ft_mouse(t_cub3D *game)
{
	/* red cross */

	ft_exit(NULL, game);
	return (0);
}
