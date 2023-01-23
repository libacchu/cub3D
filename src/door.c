/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:42:39 by obibby            #+#    #+#             */
/*   Updated: 2023/01/23 10:51:07 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	add_door(t_cub3D *game, int x, int y)
{
	t_door	*new_door;
	t_door	*door;

	new_door = ft_calloc(1, sizeof(t_door));
	if (!new_door)
		return (err_message("Failed to allocate memory.\n"));
	new_door->x = x;
	new_door->y = y;
	new_door->open = 0;
	new_door->next = NULL;
	if (!game->door_list)
		game->door_list = new_door;
	else
	{
		door = game->door_list;
		while (door->next)
			door = door->next;
		door->next = new_door;
	}
	return (0);
}

int	assign_door(t_cub3D *game)
{
	int	x;
	int	y;

	game->door.img = mlx_xpm_file_to_image(game->mlx,
			"textures/imgs/door.xpm", &x, &y);
	if (!game->door.img)
		return (err_message("Door image not loaded!"));
	game->door.addr = mlx_get_data_addr(game->door.img,
			&game->door.bpp, &game->door.line_size,
			&game->door.endian);
	return (0);
}

int	check_door(t_cub3D *game, int side)
{
	t_door	*door;

	door = game->door_list;
	while (door)
	{
		if (door->x == game->ray.map_x && door->y == game->ray.map_y)
		{
			get_perp_wall_dist(game, side);
			get_draw_coords(game);
			get_tex_pos(game, side);
			if (game->ray.tex_x < 130 || game->ray.tex_x > RESOLUTION - 125)
				return (1);
			if (!door->open)
			{
				game->door_hit = 1;
				return (1);
			}
			break ;
		}
		door = door->next;
	}
	return (0);
}

void	get_door_colour(t_cub3D *game, t_image *img, int x, int y)
{
	int	colour;

	game->ray.tex_y = (int)(game->ray.tex_pos) & (RESOLUTION - 1);
	game->ray.tex_pos += game->ray.step;
	colour = *(int *)(img->addr + game->ray.tex_y % RESOLUTION * img->line_size
			+ (game->ray.tex_x) % RESOLUTION * (img->bpp / 8));
	my_mlx_pixel_put(&game->img, x, y, colour);
}

void	find_door(t_cub3D *game)
{
	if (game->player.dir_x > 0.5 && game->map_arr[(int)game->player.pos_y]
		[(int)game->player.pos_x + 1] == 'D')
		open_door(game, game->player.pos_x + 1, game->player.pos_y);
	else if (game->player.dir_x < -0.5 && game->map_arr[(int)game->player.pos_y]
		[(int)game->player.pos_x - 1] == 'D')
		open_door(game, game->player.pos_x - 1, game->player.pos_y);
	else if (game->player.dir_y > 0.5 && game->map_arr
		[(int)game->player.pos_y + 1][(int)game->player.pos_x] == 'D')
		open_door(game, game->player.pos_x, game->player.pos_y + 1);
	else if (game->player.dir_y < -0.5 && game->map_arr
		[(int)game->player.pos_y - 1][(int)game->player.pos_x] == 'D')
		open_door(game, game->player.pos_x, game->player.pos_y - 1);
}
