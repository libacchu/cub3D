/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:42:39 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 16:17:19 by obibby           ###   ########.fr       */
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
		if (door->x == game->ray.mapX && door->y == game->ray.mapY)
		{
			get_perp_wall_dist(game, side);
			get_draw_coords(game);
			get_tex_pos(game, side);
			if (game->ray.texX < 130 || game->ray.texX > 512 - 125)
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

	game->ray.texY = (int)(game->ray.tex_pos) & (512 - 1);
	game->ray.tex_pos += game->ray.step;
	colour = *(int *)(img->addr + game->ray.texY % 512 * img->line_size
			+ (game->ray.texX) % 512 * (img->bpp / 8));
	my_mlx_pixel_put(&game->img, x, y, colour);
}

void	find_door(t_cub3D *game)
{
	if (game->player.dirX > 0.5 && game->map_arr[(int)game->player.posY]
		[(int)game->player.posX + 1] == 'D')
		open_door(game, game->player.posX + 1, game->player.posY);
	else if (game->player.dirX < -0.5 && game->map_arr[(int)game->player.posY]
		[(int)game->player.posX - 1] == 'D')
		open_door(game, game->player.posX - 1, game->player.posY);
	else if (game->player.dirY > 0.5 && game->map_arr
		[(int)game->player.posY + 1][(int)game->player.posX] == 'D')
		open_door(game, game->player.posX, game->player.posY + 1);
	else if (game->player.dirY < -0.5 && game->map_arr
		[(int)game->player.posY - 1][(int)game->player.posX] == 'D')
		open_door(game, game->player.posX, game->player.posY - 1);
}
