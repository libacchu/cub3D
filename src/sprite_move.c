/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:49:37 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 16:06:47 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_sprite(t_cub3D *game, int *sprite_order, int i)
{
	if (ft_abs(game->player.posX - game->sprite_arr[i]->x) < 3
		&& ft_abs(game->player.posY - game->sprite_arr[i]->y) < 3)
	{
		if (!game->sprite_arr[i]->sprite_scare)
		{
			game->sprite_arr[i]->sp_anime = 2;
			game->sprite_arr[i]->sp_img = 1;
			game->sprite_arr[i]->sprite_scare = 1;
			if (!fork())
			{
				system("afplay sound/scream.mp3");
				exit(0);
			}
		}
		game->sprite_arr[sprite_order[i]]->x += 0.2
			* (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
		game->sprite_arr[sprite_order[i]]->y += 0.2
			* (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
	}
	game->sprite_arr[sprite_order[i]]->x += 0.003
		* (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
	game->sprite_arr[sprite_order[i]]->y += 0.003
		* (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
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
