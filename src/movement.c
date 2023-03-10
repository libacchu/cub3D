/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:30:01 by obibby            #+#    #+#             */
/*   Updated: 2023/01/19 09:43:58 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_player(t_cub3D *game, int dir)
{
	double	old_x;

	old_x = game->player.dir_x;
	if (dir == 1)
	{
		game->player.dir_x = old_x * cos(ROTATE_SPEED)
			- game->player.dir_y * sin(ROTATE_SPEED);
		game->player.dir_y = old_x * sin(ROTATE_SPEED)
			+ game->player.dir_y * cos(ROTATE_SPEED);
		old_x = game->player.view_x;
		game->player.view_x = old_x * cos(ROTATE_SPEED)
			- game->player.view_y * sin(ROTATE_SPEED);
		game->player.view_y = old_x * sin(ROTATE_SPEED)
			+ game->player.view_y * cos(ROTATE_SPEED);
		return ;
	}
	game->player.dir_x = old_x * cos(-ROTATE_SPEED)
		- game->player.dir_y * sin(-ROTATE_SPEED);
	game->player.dir_y = old_x * sin(-ROTATE_SPEED)
		+ game->player.dir_y * cos(-ROTATE_SPEED);
	old_x = game->player.view_x;
	game->player.view_x = old_x * cos(-ROTATE_SPEED)
		- game->player.view_y * sin(-ROTATE_SPEED);
	game->player.view_y = old_x * sin(-ROTATE_SPEED)
		+ game->player.view_y * cos(-ROTATE_SPEED);
}

void	move_left_down(t_cub3D *game, double speed_x, double speed_y)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->player.pos_x - speed_x);
	new_y = (int)(game->player.pos_y - speed_y);
	if (game->map_arr[(int)game->player.pos_y][new_x] != '1' &&
		(game->map_arr[(int)game->player.pos_y][new_x] != 'D'
		|| find_door_node(game, new_x, new_y)))
		game->player.pos_x -= speed_x;
	if (game->map_arr[new_y][(int)game->player.pos_x] != '1' &&
		(game->map_arr[new_y][(int)game->player.pos_x] != 'D'
		|| find_door_node(game, new_x, new_y)))
		game->player.pos_y -= speed_y;
}

void	move_right_up(t_cub3D *game, double speed_x, double speed_y)
{
	int	new_x;
	int	new_y;

	new_x = (int)(game->player.pos_x + speed_x);
	new_y = (int)(game->player.pos_y + speed_y);
	if (game->map_arr[(int)game->player.pos_y][new_x] != '1' &&
		(game->map_arr[(int)game->player.pos_y][new_x] != 'D'
		|| find_door_node(game, new_x, new_y)))
		game->player.pos_x += speed_x;
	if (game->map_arr[new_y][(int)game->player.pos_x] != '1' &&
		(game->map_arr[new_y][(int)game->player.pos_x] != 'D'
		|| find_door_node(game, new_x, new_y)))
		game->player.pos_y += speed_y;
}

void	check_sprite_proximity(t_cub3D *game)
{
	int	i;

	i = -1;
	while (game->sprite_arr[++i])
	{
		if (!game->sprite_arr[i]->sprite_active
			&& ft_abs(game->player.pos_x - game->sprite_arr[i]->x) < 5
			&& ft_abs(game->player.pos_y - game->sprite_arr[i]->y) < 5)
		{
			game->sprite_arr[i]->sp_anime = 0;
			game->sprite_arr[i]->sp_img = 0;
			game->sprite_arr[i]->sprite_activate = 1;
		}
		else if (game->sprite_arr[i]->sprite_active
			&& !game->sprite_arr[i]->sprite_deactivate
			&& (ft_abs(game->player.pos_x - game->sprite_arr[i]->x) > 5
				|| ft_abs(game->player.pos_y - game->sprite_arr[i]->y) > 5))
			game->sprite_arr[i]->sprite_deactivate = 1;
		else if (game->sprite_arr[i]->sprite_scare
			&& (ft_abs(game->player.pos_x - game->sprite_arr[i]->x) > 3
				|| ft_abs(game->player.pos_y - game->sprite_arr[i]->y) > 3))
			game->sprite_arr[i]->sprite_scare = 0;
	}
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
	check_sprite_proximity(game);
}
