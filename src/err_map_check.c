/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_map_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:49:11 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/18 16:16:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_x(int c)
{
	if (check_chars(c))
	{
		if (c == ' ')
			return (err_message("Map is not enclosed with walls."));
		return (err_message("Invalid character in map."));
	}
	return (0);
}

int	check_y(char **map_arr, int y, int x)
{
	if ((int)ft_strlen(map_arr[y]) < x + 1 || check_chars(map_arr[y][x]))
	{
		if ((int)ft_strlen(map_arr[y]) < x + 1 || map_arr[y][x] == ' ')
			return (err_message("Map is not enclosed with walls."));
		return (err_message("Invalid character in map."));
	}
	return (0);
}

int	check_walls_chars(t_cub3D *game, int x, int y)
{
	if (game->map_arr[y][x] != ' ' && check_chars(game->map_arr[y][x]))
		return (err_message("Invalid character in map."));
	if (game->map_arr[y][x] != '1' && game->map_arr[y][x] > 32)
	{
		if ((x == 0 || y == 0 \
			|| !game->map_arr[y][x + 1] || !game->map_arr[y + 1]))
			return (err_message("Map is not enclosed with walls."));
		if (check_x(game->map_arr[y][x + 1]))
			return (1);
		if (check_x(game->map_arr[y][x - 1]))
			return (1);
		if (check_y(game->map_arr, y + 1, x))
			return (1);
		if (check_y(game->map_arr, y - 1, x))
			return (1);
	}
	return (0);
}

int	loop_x(t_cub3D *game, int x, int y)
{
	while (game->map_arr[y][++x])
	{
		if (ft_strchr("NSEW", game->map_arr[y][x]))
		{
			if (!game->player.direct)
				player_start_direction(x, y, game);
			else
				return (err_message("Too many player starts in map."));
		}
		else if (game->map_arr[y][x] == 'D')
		{
			if (add_door(game, x, y))
				return (1);
		}
		else if (game->map_arr[y][x] == 'G')
		{
			if (add_sprite(game, x, y))
				return (1);
		}
		if (check_walls_chars(game, x, y))
			return (1);
	}
	if (game->minimap_size_x < x)
		game->minimap_size_x = x;
	return (0);
}

int	check_map(char *str, t_cub3D *game, int fd)
{
	int	x;
	int	y;

	if (create_map_arr(str, game, fd))
		return (1);
	y = -1;
	while (game->map_arr[++y])
	{
		x = -1;
		if (loop_x(game, x, y))
			return (1);
	}
	game->minimap_size_y = y * 34;
	game->minimap_size_x *= 34;
	if (!game->player.direct)
		return (err_message("No player location in map."));
	return (0);
}
