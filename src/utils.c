/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:42:55 by obibby            #+#    #+#             */
/*   Updated: 2023/01/15 23:41:08 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

double	ft_abs(double x)
{
	if (x < 0)
		x = -x;
	return (x);
}

void	open_door(t_cub3D *game, int x, int y)
{
	t_door	*door;

	door = game->door_list;
	while (door)
	{
		if (door->x == x && door->y == y)
		{
			if (!door->open)
				door->open = 1;
			else
				door->open = 0;
			break ;
		}
		door = door->next;
	}
}
