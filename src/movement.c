/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:30:01 by obibby            #+#    #+#             */
/*   Updated: 2023/01/14 15:30:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_player(t_cub3D *game, int dir)
{
	double	old_x;

	old_x = game->player.dirX;
	if (dir == 1)
	{
		game->player.dirX = old_x * cos(ROTATE_SPEED)
			- game->player.dirY * sin(ROTATE_SPEED);
		game->player.dirY = old_x * sin(ROTATE_SPEED)
			+ game->player.dirY * cos(ROTATE_SPEED);
		old_x = game->player.viewX;
		game->player.viewX = old_x * cos(ROTATE_SPEED)
			- game->player.viewY * sin(ROTATE_SPEED);
		game->player.viewY = old_x * sin(ROTATE_SPEED)
			+ game->player.viewY * cos(ROTATE_SPEED);
		return ;
	}
	game->player.dirX = old_x * cos(-ROTATE_SPEED)
		- game->player.dirY * sin(-ROTATE_SPEED);
	game->player.dirY = old_x * sin(-ROTATE_SPEED)
		+ game->player.dirY * cos(-ROTATE_SPEED);
	old_x = game->player.viewX;
	game->player.viewX = old_x * cos(-ROTATE_SPEED)
		- game->player.viewY * sin(-ROTATE_SPEED);
	game->player.viewY = old_x * sin(-ROTATE_SPEED)
		+ game->player.viewY * cos(-ROTATE_SPEED);
}

void	move_player(t_cub3D *game, double y, double x, int grad)
{
	double	speed;

	if (game->shift)
		speed = RUN_SPEED;
	else
		speed = WALK_SPEED;
	if (grad < 0)
	{
		game->player.posY -= speed * y;
		game->player.posX -= speed * x;
	}
	else
	{
		game->player.posY += speed * y;
		game->player.posX += speed * x;
	}
}
