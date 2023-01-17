/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:42:55 by obibby            #+#    #+#             */
/*   Updated: 2023/01/17 12:38:19 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_swap(int *distance_x, int *distance_y, int *order_x, int *order_y)
{
	int z;
	
	z = *distance_x;
	*distance_x = *distance_y;
	*distance_y = z;
	z = *order_x;
	*order_x = *order_y;
	*order_y = z;
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

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
