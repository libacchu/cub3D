/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_tex_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:27:27 by obibby            #+#    #+#             */
/*   Updated: 2023/01/12 18:25:35 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	alloc_wall(char *str, void **wall_ptr)
{
	if (*wall_ptr)
		return (err_message("Too many textures in mapfile."));
	*wall_ptr = ft_strtrim(str, " 	\n");
	if (!*wall_ptr)
		return (err_message("Memory allocation failed."));
	return (0);
}

int	check_tex(char *str, t_cub3D *game)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ' && str[3])
	{
		if (alloc_wall(&str[3], &game->north_wall.img))
			return (1);
	}
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ' && str[3])
	{
		if (alloc_wall(&str[3], &game->south_wall.img))
			return (1);
	}
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ' && str[3])
	{
		if (alloc_wall(&str[3], &game->west_wall.img))
			return (1);
	}
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ' && str[3])
	{
		if (alloc_wall(&str[3], &game->east_wall.img))
			return (1);
	}
	else
		return (1);
	return (0);
}
