/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:28:42 by obibby            #+#    #+#             */
/*   Updated: 2023/01/19 14:38:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	err_message(char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

int	err_path_name(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
	{
		err_message("Invalid file extension.");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		err_message("File doesn't exist!");
	return (fd);
}

int	only_white_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 32)
			return (0);
	}
	return (1);
}

int	errorcheck(char **argv, t_cub3D *game)
{
	int	fd;

	game->path = argv[1];
	fd = err_path_name(game->path);
	if (fd == -1)
		return (1);
	if (err_map(fd, game))
		return (1);
	close(fd);
	return (0);
}
