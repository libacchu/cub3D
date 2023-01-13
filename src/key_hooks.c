/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:11:01 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/13 23:03:40 by obibby           ###   ########.fr       */
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
	double speed;

	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
		ft_exit(NULL, game);
	else if (keycode == KEY_W)
	{
		if (game->shift)
			speed = RUN_SPEED;
		else
			speed = WALK_SPEED;
		game->player.posY += speed * game->player.dirY;
		game->player.posX += speed * game->player.dirX;
	}
	else if (keycode == KEY_A)
	{
		if (game->shift)
			speed = RUN_SPEED;
		else
			speed = WALK_SPEED;
		game->player.posY -= speed * game->player.viewY;
		game->player.posX -= speed * game->player.viewX;
	}
	else if (keycode == KEY_S)
	{
		if (game->shift)
			speed = RUN_SPEED;
		else
			speed = WALK_SPEED;
		game->player.posY -= speed * game->player.dirY;
		game->player.posX -= speed * game->player.dirX;
	}
	else if (keycode == KEY_D)
	{
		if (game->shift)
			speed = RUN_SPEED;
		else
			speed = WALK_SPEED;
		game->player.posY += speed * game->player.viewY;
		game->player.posX += speed * game->player.viewX;
	}
	else if (keycode == KEY_LEFT)
	{
		double	old_X;
		old_X = game->player.dirX;
		game->player.dirX = old_X * cos(-ROTATE_SPEED) - game->player.dirY * sin(-ROTATE_SPEED);
		game->player.dirY = old_X * sin(-ROTATE_SPEED) + game->player.dirY * cos(-ROTATE_SPEED);
		old_X = game->player.viewX;
		game->player.viewX = old_X * cos(-ROTATE_SPEED) - game->player.viewY * sin(-ROTATE_SPEED);
		game->player.viewY = old_X * sin(-ROTATE_SPEED) + game->player.viewY * cos(-ROTATE_SPEED);
	}
	else if (keycode == KEY_RIGHT)
	{
		double	old_X;
		old_X = game->player.dirX;
		game->player.dirX = old_X * cos(ROTATE_SPEED) - game->player.dirY * sin(ROTATE_SPEED);
		game->player.dirY = old_X * sin(ROTATE_SPEED) + game->player.dirY * cos(ROTATE_SPEED);
		old_X = game->player.viewX;
		game->player.viewX = old_X * cos(ROTATE_SPEED) - game->player.viewY * sin(ROTATE_SPEED);
		game->player.viewY = old_X * sin(ROTATE_SPEED) + game->player.viewY * cos(ROTATE_SPEED);
	}
	else if (keycode == KEY_TAB)
	{
		if (game->tab)
		{
			game->tab = 0;
			game->map_gen = 0;
		}
		else
			game->tab = 1;
	}
	else if (keycode == KEY_SHIFT)
	{
		if (game->shift)
			game->shift = 0;
		else
			game->shift = 1;
	}
	return (0);
}

int	ft_mouse(t_cub3D *game)
{
	/* red cross */

	ft_exit(NULL, game);
	return (0);
}
