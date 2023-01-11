/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:43:11 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 10:43:18 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	err_map(int fd, t_cub3D *game)
{
	char *str;
	int i;
	int flag;
	
	flag = 0;
	i = 0;
	str = get_next_line(fd);
	while (str && i != 6)
	{
		if (!not_only_white_space(str))
		{
			free(str);
			str = get_next_line(fd);
			continue ;
		}
		else
		{
			ft_printf(str);
			if (str[0] == 'F' || str[0] == 'C')
			{
				if (check_rgb(str, game))
					return (err_message("Invalid colour variable in map file."));
			}
			else if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3) || !ft_strncmp(str, "EA ", 3) || !ft_strncmp(str, "WE ", 3) )
			{
				if (check_tex(str, game))
					return (1);
			}
			else
				return (err_message("Invalid or missing variable in map file."));
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	if (i && !str)
		return (err_message("No map."));
	else if (i == 6 && check_map(str, game, fd))
		return (1);
	if (i == 0 )
		return (err_message("Empty file."));
	if (i < 6)
		return (err_message("Invalid map file."));
	return (0);
}
