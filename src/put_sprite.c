/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:53 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 17:19:08 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_sprite_colour(t_cub3D *game, int tex_x, int x, int y)
{
	int			tex_y;
	int			d;
	int			colour;
	t_sprite	*sprite;

	sprite = game->sprite_arr[game->sprite_order[game->sprite_info.index]];
	d = y * 256 - game->window_height * 128 + game->sprite_info.s_height * 128;
	tex_y = ((d * RESOLUTION) / game->sprite_info.s_height) / 256;
	colour = *(int *)(game->sprite[sprite->sp_anime].addr + ((tex_y / 8) % 64)
			* game->sprite[sprite->sp_anime].line_size
			+ (((tex_x / 8) % 64) + 64 * sprite->sp_img)
			* (game->sprite[sprite->sp_anime].bpp / 8));
	if ((colour & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&game->img, x, y, colour);
}

void	put_sprite(t_cub3D *game, t_spr_cast *info)
{
	int	x;
	int	tex_x;
	int	y;

	x = info->draw_start_x - 1;
	while (++x < info->draw_end_x)
	{
		tex_x = (int)(256 * (x - (-info->s_width / 2 + info->s_screen_x))
				* RESOLUTION / info->s_width / 256);
		if (info->trans_y > 0 && x > 0 && x < game->window_width
			&& info->trans_y < game->ray.zbuffer[x])
		{
			y = info->draw_start_y - 1;
			while (++y < info->draw_end_y)
				put_sprite_colour(game, tex_x, x, y);
		}
	}
}

int	draw_sprites(t_cub3D *game)
{
	if (get_sprite_dist(game))
		return (1);
	game->sprite_info.index = -1;
	while (++game->sprite_info.index < game->sprite_total)
	{
		if (!game->sprite_arr[game->sprite_order
				[game->sprite_info.index]]->sprite_active)
			continue ;
		move_sprite(game, game->sprite_order[game->sprite_info.index]);
		get_sprite_size(game, &game->sprite_info, game->sprite_info.index);
		get_sprite_coords(game, &game->sprite_info);
		put_sprite(game, &game->sprite_info);
	}
	free(game->sprite_order);
	return (0);
}
