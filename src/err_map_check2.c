/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_map_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:49:11 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/15 12:36:28 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_rows(char *path)
{
	int		fd;
	char	*str;
	int		count;

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

int	add_to_arr(char **str, t_cub3D *game, int fd)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (!only_white_space(*str))
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
	while (only_white_space(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	if (add_to_arr(&str, game, fd))
		return (1);
	return (0);
}

int	check_chars(char c)
{
	char	*list;

	list = "01DNSEW";
	if (ft_strchr(list, c))
		return (0);
	return (1);
}
