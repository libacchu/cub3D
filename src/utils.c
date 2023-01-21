/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:42:55 by obibby            #+#    #+#             */
/*   Updated: 2023/01/20 12:20:28 by libacchu         ###   ########.fr       */
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
	int	z;

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

void	play_sound(char *str)
{
	if (SYSTEM == 1)
	{
		if (!fork())
		{
			system(str);
			exit(0);
		}
	}
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
