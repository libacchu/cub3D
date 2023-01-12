/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_rgb_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:59:43 by obibby            #+#    #+#             */
/*   Updated: 2023/01/11 11:08:18 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	set_rgb(char *str, int *colour)
{
	int	shift;
	int	n;
	int	i;

	shift = 16;
	i = 1;
	while (shift >= 8)
	{
		while (str[i] && (str[i] <= 32 || str[i] == ','))
			i++;
		if (!str[i] || !ft_isdigit(str[i]))
			return (1);
		n = ft_atoi(&str[i]);
		if (n > 255 || n < 0)
			return (1);
		*colour = *colour | n;
		*colour = *colour << shift;
		while (str[i] && str[i] != ',')
			i++;
		i++;
		shift -= 4;
	}
	return (0);
}

int	check_rgb(char *str, t_cub3D *game)
{
	if (str[0] == 'C')
	{
		if (set_rgb(str, &game->ceiling))
			return (1);
	}
	else
	{
		if (set_rgb(str, &game->floor))
			return (1);
	}
	return (0);
}
