/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:30:01 by obibby            #+#    #+#             */
/*   Updated: 2023/01/15 22:14:11 by libacchu         ###   ########.fr       */
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

void	move_left_down(t_cub3D *game, double speed_x, double speed_y)
{
	int new_x;
	int new_y;

	new_x = (int)(game->player.posX - speed_x);
	new_y = (int)(game->player.posY - speed_y);
	if (game->map_arr[(int)game->player.posY][new_x] != '1')
		game->player.posX -= speed_x;
	if (game->map_arr[new_y][(int)game->player.posX] != '1')
		game->player.posY -= speed_y;
}

void	move_right_up(t_cub3D *game, double speed_x, double speed_y)
{
	int new_x;
	int new_y;

	new_x = (int)(game->player.posX + speed_x);
	new_y = (int)(game->player.posY + speed_y);
	if (game->map_arr[(int)game->player.posY][new_x] != '1')
		game->player.posX += speed_x;
	if (game->map_arr[new_y][(int)game->player.posX] != '1')
		game->player.posY += speed_y;
}

void	move_player(t_cub3D *game, double y, double x, int grad)
{
	double	speed;
	double	speed_x;
	double	speed_y;
	

	if (game->shift)
		speed = RUN_SPEED;
	else
		speed = WALK_SPEED;
	speed_x = speed * x;
	speed_y = speed * y;
	if (grad < 0)
		move_left_down(game, speed_x, speed_y);
	else
		move_right_up(game, speed_x, speed_y);
}
