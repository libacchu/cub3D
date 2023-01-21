/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:55:01 by obibby            #+#    #+#             */
/*   Updated: 2023/01/16 00:18:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	make_minimap(t_cub3D *game)
{
	game->minimap.img = mlx_new_image(game->mlx, game->minimap_size_x + 20,
			game->minimap_size_y + 20);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bpp, &game->minimap.line_size,
			&game->minimap.endian);
}

void	refresh_minimap(t_cub3D *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map_arr[++y])
	{
		x = -1;
		while (game->map_arr[y][++x])
		{
			if (game->map_arr[y][x] == '1' || game->map_arr[y][x] == ' ')
				pixel_put_image(game, &game->minimap_wall, x, y);
			else
				pixel_put_image(game, &game->minimap_floor, x, y);
		}
	}
}
