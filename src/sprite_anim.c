/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:42:41 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 15:45:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	scare_sprite(t_cub3D *game, int i)
{
	if (game->sprite_arr[i]->sp_img > 3)
		game->sprite_arr[i]->sp_img = 2;
}

void	deactivate_scare(t_cub3D *game, int i)
{
	game->sprite_arr[i]->sp_img -= 2;
	if (game->sprite_arr[i]->sp_img < 0)
	{
		game->sprite_arr[i]->sp_anime = 1;
		game->sprite_arr[i]->sp_img = 0;
	}
}

void	deactivate_sprite(t_cub3D *game, int i)
{
	if (game->sprite_arr[i]->sprite_deactivate == 1)
	{
		game->sprite_arr[i]->sp_anime = 3;
		game->sprite_arr[i]->sp_img = 1;
	}
	game->sprite_arr[i]->sprite_deactivate++;
	if (game->sprite_arr[i]->sprite_deactivate == 7)
	{
		game->sprite_arr[i]->sprite_active = 0;
		game->sprite_arr[i]->sprite_deactivate = 0;
	}
}

void	activate_sprite(t_cub3D *game, int i)
{
	if (game->sprite_arr[i]->sprite_activate == 1)
	{
		game->sprite_arr[i]->sp_anime = 0;
		game->sprite_arr[i]->sp_img = 0;
		game->sprite_arr[i]->sprite_active = 1;
	}
	if (game->sprite_arr[i]->sp_img == game->sprite_arr[i]
		->sp_img_total[game->sprite_arr[i]->sp_anime])
	{
		game->sprite_arr[i]->sp_anime++;
		game->sprite_arr[i]->sp_img = 0;
	}
	game->sprite_arr[i]->sprite_activate++;
	if (game->sprite_arr[i]->sprite_activate == 15)
	{
		game->sprite_arr[i]->sprite_activate = 0;
		game->sprite_arr[i]->sp_img = 0;
	}
}

void	idle_sprite(t_cub3D *game, int i)
{
	game->sprite_arr[i]->sp_anime = 1;
	game->sprite_arr[i]->sp_img = game->sprite_arr[i]->sp_img
		% game->sprite_arr[i]
		->sp_img_total[game->sprite_arr[i]->sp_anime];
}
