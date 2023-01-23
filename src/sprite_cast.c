/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:46:37 by obibby            #+#    #+#             */
/*   Updated: 2023/01/23 11:22:09 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	sort_sprites(int *sprite_order, int *sprite_distance, int total_sprites)
{
	int	x;
	int	y;

	x = 0;
	while (x < total_sprites)
	{
		y = x + 1;
		while (y < total_sprites)
		{
			if (sprite_distance[y] > sprite_distance[x])
				ft_swap(&sprite_distance[x], &sprite_distance[y],
					&sprite_order[x], &sprite_order[y]);
			y++;
		}
		x++;
	}
}

int	get_sprite_dist(t_cub3D *game)
{
	int	i;

	game->sprite_order = ft_calloc(game->sprite_total, sizeof(int));
	if (!game->sprite_order)
		return (err_message("Memory allocation failed."));
	game->sprite_distance = ft_calloc(game->sprite_total, sizeof(int));
	if (!game->sprite_distance)
		return (err_message("Memory allocation failed."));
	i = 0;
	while (game->sprite_arr[i])
	{
		game->sprite_order[i] = i;
		game->sprite_distance[i] = ((game->player.pos_x - \
			game->sprite_arr[i]->x)
				* (game->player.pos_x - game->sprite_arr[i]->x)
				+ (game->player.pos_y - game->sprite_arr[i]->y)
				* (game->player.pos_y - game->sprite_arr[i]->y));
		i++;
	}
	sort_sprites(game->sprite_order, game->sprite_distance, game->sprite_total);
	free(game->sprite_distance);
	return (0);
}

void	get_sprite_coords(t_cub3D *game, t_spr_cast *info)
{
	info->draw_start_y = -info->s_height * 0.5 + game->half_height;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->s_height * 0.5 + game->half_height;
	if (info->draw_end_y >= game->window_height)
		info->draw_end_y = game->window_height - 1;
	info->draw_start_x = -info->s_width * 0.5 + info->s_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->s_width * 0.5 + info->s_screen_x;
	if (info->draw_end_x >= game->window_width)
		info->draw_end_x = game->window_width - 1;
}

void	get_sprite_size(t_cub3D *game, t_spr_cast *info, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	trans_x;

	sprite_x = game->sprite_arr[game->sprite_order[i]]->x - game->player.pos_x;
	sprite_y = game->sprite_arr[game->sprite_order[i]]->y - game->player.pos_y;
	inv_det = 1.0 / (game->player.view_x * game->player.dir_y
			- game->player.dir_x * game->player.view_y);
	trans_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	info->trans_y = inv_det * (-game->player.view_y * sprite_x
			+ game->player.view_x * sprite_y);
	info->s_screen_x = (int)(game->half_width * (1 + trans_x / info->trans_y));
	info->s_height = abs((int)(game->window_height / info->trans_y));
	info->s_width = abs((int)(game->window_height / info->trans_y));
}
