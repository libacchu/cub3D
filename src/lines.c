/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:06:30 by obibby            #+#    #+#             */
/*   Updated: 2023/01/19 10:18:42 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_line(t_cub3D *game, t_line *line)
{
	while (line->x0 != line->x1 || line->y0 != line->y1)
	{
		my_mlx_pixel_put(&game->minimap, line->x0 + 10,
			line->y0 + 10, game->ray_colour);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->err2 = line->err;
		if (line->err2 > -line->dx)
		{
			line->err -= line->dy;
			line->x0 += line->sx;
		}
		if (line->err2 < line->dy)
		{
			line->err += line->dx;
			line->y0 += line->sy;
		}
	}
}

void	line_algo(t_cub3D *game, int x, int y)
{
	t_line	line;

	line.x0 = x;
	line.y0 = y;
	line.x1 = (game->ray.map_x + 0.5) * 34;
	line.y1 = (game->ray.map_y + 0.5) * 34;
	line.dx = ft_abs(line.x1 - line.x0);
	line.dy = ft_abs(line.y1 - line.y0);
	if (line.x0 < line.x1)
		line.sx = 1;
	else
		line.sx = -1;
	if (line.y0 < line.y1)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.err = line.dx / 2;
	else
		line.err = -line.dy / 2;
	draw_line(game, &line);
}
