/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_map_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:49:11 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 12:19:20 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_rows(char *path)
{
	int fd;
	char *str;
	int count;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	count = 0;
	while (str)
	{
		if (str[0] != '\n')
			count++;
		free(str);
		str = get_next_line(fd);
	}
	count -= 6;
	free(str);
	return (count);
}

int	add_to_arr(char ** str, t_cub3D *game, int fd)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (not_only_white_space(*str))
		{
			game->map_arr[i] = ft_strtrim(*str, "\n");
			if (!game->map_arr[i++])
				return (err_message("Failed to allocate memory.\n"));			
		}
		else
		{
			free(*str);
			return (0);
		}
		free(*str);
		*str = get_next_line(fd);
	}
	return (0);
}

int	create_map_arr(char *str, t_cub3D *game, int fd)
{

	game->map_arr = ft_calloc(count_rows(game->path) + 1, sizeof(char *));
	if (!game->map_arr)
		return (err_message("Failed to allocate memory.\n"));
	while (!not_only_white_space(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	if (add_to_arr(&str, game, fd))
		return (1);
	return (0);
}

int check_chars(char c)
{
	char *list;
	list = "01NSEW";
	if (ft_strchr(list, c))
		return (0);
	return (1);
}

int check_x(int c)
{
	if (check_chars(c))
	{
		if (c == ' ')
			return (err_message("Map is not enclosed with walls."));
		return (err_message("Invalid character in map."));
	}
	return (0);
}

int check_y(char **map_arr, int y, int x)
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
		if ((x == 0 || y == 0 || !game->map_arr[y][x + 1] || !game->map_arr[y + 1]))
			return (err_message("Map is not enclosed with walls."));	
		if (check_x(game->map_arr[y][x+1]))
			return (1);
		if (check_x(game->map_arr[y][x-1]))
			return (1);
		if (check_y(game->map_arr, y+1, x))
			return (1);
		if (check_y(game->map_arr, y-1, x))
			return (1);
	}
	return (0);
}

int check_map(char *str, t_cub3D *game, int fd)
{
	int x;
	int y;
	if (create_map_arr(str, game, fd))
		return (1);
	y = -1;
	while (game->map_arr[++y])
	{
		x = -1;
		while (game->map_arr[y][++x])
		{
			if (ft_strchr("NSEW", game->map_arr[y][x]))
			{
				if (!game->player.direct)
				{
					game->player.direct = game->map_arr[y][x];
					game->player.x = x;
					game->player.y = y;
				}
				else
					return (err_message("Invalid character: Check player elements."));
			}
			if (check_walls_chars(game, x, y))
				return (1);
		}
	}
	if (!game->player.direct)
		return (err_message("No player location in map."));
	return (0);
}
