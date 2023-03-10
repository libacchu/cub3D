/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:47:07 by obibby            #+#    #+#             */
/*   Updated: 2023/01/24 11:36:05 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_keys(t_cub3D *game)
{
	game->up_key = 0;
	game->down_key = 0;
	game->left_key = 0;
	game->right_key = 0;
	game->tab = 0;
	game->shift = 0;
}

void	init_imgs(t_cub3D *game)
{
	game->north_wall.img = NULL;
	game->south_wall.img = NULL;
	game->west_wall.img = NULL;
	game->east_wall.img = NULL;
	game->north_wall_addr = NULL;
	game->east_wall_addr = NULL;
	game->south_wall_addr = NULL;
	game->west_wall_addr = NULL;
	game->north_compass.img = NULL;
	game->east_compass.img = NULL;
	game->south_compass.img = NULL;
	game->west_compass.img = NULL;
	game->minimap.img = NULL;
	game->minimap_wall.img = NULL;
	game->minimap_floor.img = NULL;
	game->minimap_player.img = NULL;
}

void	init_game(t_cub3D *game)
{
	game->window = NULL;
	init_imgs(game);
	init_keys(game);
	game->player.direct = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->ceiling = 0;
	game->floor = 0;
	game->sprite_total = 0;
	game->compass = colourshift(200, 90, 120, 150);
	game->ray_colour = colourshift(100, 128, 128, 128);
	game->doors = 0;
	game->door_list = NULL;
	game->door.img = NULL;
	game->path = NULL;
	game->map_arr = NULL;
	game->minimap_size_x = 0;
	game->minimap_size_y = 0;
	game->once = 0;
	game->sprite_list = NULL;
	game->sprite_arr = NULL;
	game->sprite = NULL;
	game->ray.zbuffer = NULL;
	game->last_time = get_time_in_ms();
}

void	set_screen_size(t_cub3D *game)
{
	mlx_get_screen_size(game->mlx, &game->window_width, &game->window_height);
	if (game->window_width > 1920)
		game->window_width = 1920;
	if (game->window_height > 1080)
		game->window_height = 1080;
	game->half_height = game->window_height / 2;
	game->half_width = game->window_width / 2;
	game->mouse_prev_x = game->half_width;
	game->mouse_prev_y = game->half_height;
	game->x_left_limit = game->window_width / 15;
	game->x_right_limit = game->window_width * 14 / 15;
	game->y_up_limit = game->window_height * 14 / 15;
	game->y_down_limit = game->window_height / 15;
	game->img.img = mlx_new_image(game->mlx, game->window_width,
			game->window_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_size, &game->img.endian);
}
