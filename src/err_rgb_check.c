/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_rgb_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:59:43 by obibby            #+#    #+#             */
/*   Updated: 2023/01/14 10:21:20 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	set_rgb(char *str, int *colour)
{
	int	n;
	int	i;
	int r;
	int g;
	int b;
	int c;

	i = 1;
	c = 0;
	while (c < 3)
	{
		while (str[i] && (str[i] <= 32 || str[i] == ','))
			i++;
		if (!str[i] || !ft_isdigit(str[i]))
			return (1);
		n = ft_atoi(&str[i]);
		if (n > 255 || n < 0)
			return (1);
		if (c == 0)
			r = n;
		else if (c == 1)
			g = n;
		else if (c == 2)
			b = n;
		while (str[i] && str[i] != ',')
			i++;
		i++;
		c++;
	}
	*colour = colourshift(0, r, g, b);
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
