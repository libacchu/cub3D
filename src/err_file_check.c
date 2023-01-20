/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:43:11 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/20 10:56:39 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	map_checks(t_cub3D *game, char **str, int fd, int i)
{
	if (i && !*str)
		return (err_message("No map."));
	else if (i == 6 && check_map(str, game, fd))
		return (1);
	if (i == 0)
		return (err_message("Empty file."));
	if (i < 6)
		return (err_message("Invalid map file."));
	return (0);
}

int	premap_check(t_cub3D *game, char *str)
{
	if (str[0] == 'F' || str[0] == 'C')
	{
		if (check_rgb(str, game))
			return (err_message("Invalid colour element in map file."));
	}
	else if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "EA ", 3) || !ft_strncmp(str, "WE ", 3))
	{
		if (check_tex(str, game))
			return (1);
	}
	else
		return (err_message("Invalid or missing element in map file."));
	return (0);
}

int	err_check_if_invalid_file(int i, int err)
{
	if (i == 0)
		return (err_message("Empty file."));
	else if (i < 6 && err != 1)
		return (err_message("Invalid map file."));
	else if (i == 6 && err != 1)
		return (err_message("No map."));
	return (0);
}

int	err_map(int fd, t_cub3D *game)
{
	char	*str;
	int		i;
	int		err;

	i = 0;
	err = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (!err && i <= 6 && !only_white_space(str))
		{
			if (i < 6 && premap_check(game, str))
				err = 1;
			else if (i == 6 && check_map(&str, game, fd))
				err = 1;
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	if (err_check_if_invalid_file(i, err))
		return (1);
	return (err);
}
