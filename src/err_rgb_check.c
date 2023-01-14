/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_rgb_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:59:43 by obibby            #+#    #+#             */
/*   Updated: 2023/01/14 16:01:20 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	colourshift(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_color(int **rgb, int c, int n)
{
	if (c == 0)
		*rgb[0] = n;
	else if (c == 1)
		*rgb[1] = n;
	else if (c == 2)
		*rgb[2] = n;
}

int	convert_number(char *str, int *i, int *n)
{
	while (str[*i] && (str[*i] <= 32 || str[*i] == ','))
		*i = *i + 1;
	if (!(str[*i]) || !ft_isdigit(str[*i]))
		return (1);
	*n = ft_atoi(&str[*i]);
	if (*n > 255 || *n < 0)
		return (1);
	return (0);
}

int	set_rgb(char *str, int *colour)
{
	int	n;
	int	i;
	int	c;
	int	rgb[3];

	i = 1;
	c = -1;
	while (++c < 3)
	{
		if (convert_number(str, &i, &n))
			return (1);
		if (c == 0)
			rgb[0] = n;
		else if (c == 1)
			rgb[1] = n;
		else if (c == 2)
			rgb[2] = n;
		while (str[i] && str[i] != ',')
			i++;
		i++;
	}
	ft_printf("R = %d, G = %d, B = %d \n", rgb[0], rgb[1], rgb[2]);
	*colour = colourshift(0, rgb[0], rgb[1], rgb[2]);
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
