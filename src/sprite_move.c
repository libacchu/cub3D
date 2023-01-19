/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:37 by obibby            #+#    #+#             */
/*   Updated: 2023/01/19 10:23:11 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_sprite(t_cub3D *game, int i)
{
	if (!game->sprite_arr[i]->sprite_activate
		&& ft_abs(game->player.pos_x - game->sprite_arr[i]->x) < 2.5
		&& ft_abs(game->player.pos_y - game->sprite_arr[i]->y) < 2.5)
	{
		if (!game->sprite_arr[i]->sprite_scare)
		{
			game->sprite_arr[i]->sp_anime = 2;
			game->sprite_arr[i]->sp_img = 1;
			game->sprite_arr[i]->sprite_scare = 1;
			play_sound("afplay sound/scream.mp3");
		}
		game->sprite_arr[i]->x += 0.2
			* (game->player.pos_x - game->sprite_arr[i]->x);
		game->sprite_arr[i]->y += 0.2
			* (game->player.pos_y - game->sprite_arr[i]->y);
	}
	else
	{
		game->sprite_arr[i]->x += 0.005
			* (game->player.pos_x - game->sprite_arr[i]->x);
		game->sprite_arr[i]->y += 0.005
			* (game->player.pos_y - game->sprite_arr[i]->y);
	}
}

void	inc_anims(t_cub3D *game)
{
	int	i;

	i = -1;
	game->current_time = get_time_in_ms();
	if (game->current_time - game->last_time >= 150)
	{
		while (game->sprite_arr[++i])
		{
			game->sprite_arr[i]->sp_img++;
			if (game->sprite_arr[i]->sprite_scare)
				scare_sprite(game, i);
			else if (game->sprite_arr[i]->sp_anime == 2)
				deactivate_scare(game, i);
			else if (game->sprite_arr[i]->sprite_activate)
				activate_sprite(game, i);
			else if (game->sprite_arr[i]->sprite_deactivate)
				deactivate_sprite(game, i);
			else
				idle_sprite(game, i);
		}
		game->last_time = game->current_time;
	}
}
