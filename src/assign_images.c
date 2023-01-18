/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:41:04 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 16:17:40 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	assign_compass(t_cub3D *game)
{
	int	x;
	int	y;

	game->north_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/compass/n.xpm", &x, &y);
	game->east_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/compass/e.xpm", &x, &y);
	game->south_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/compass/s.xpm", &x, &y);
	game->west_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/compass/w.xpm", &x, &y);
	if (!game->north_compass.img || !game->east_compass.img \
		|| !game->south_compass.img || !game->west_compass.img)
		return (err_message("Compass image not loaded!"));
	add_data_addr(&game->north_compass);
	add_data_addr(&game->east_compass);
	add_data_addr(&game->south_compass);
	add_data_addr(&game->west_compass);
	return (0);
}

int	assign_minimap(t_cub3D *game)
{
	int	x;
	int	y;

	game->minimap_wall.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/minimap/whiteb.xpm", &x, &y);
	game->minimap_floor.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/minimap/blackb.xpm", &x, &y);
	game->minimap_player.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/minimap/gui.xpm", &x, &y);
	if (!game->minimap_wall.img || !game->minimap_floor.img
		|| !game->minimap_player.img)
		return (err_message("Minimap image not loaded!"));
	add_data_addr(&game->minimap_wall);
	add_data_addr(&game->minimap_floor);
	add_data_addr(&game->minimap_player);
	return (0);
}

int	assign_walls_ns(t_cub3D *game)
{
	char	*ptr;
	int		x;
	int		y;

	ptr = game->north_wall.img;
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	ptr = game->south_wall.img;
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	if (!game->north_wall.img || !game->south_wall.img)
		return (err_message("Wall image not loaded!"));
	add_data_addr(&game->north_wall);
	add_data_addr(&game->south_wall);
	return (0);
}

int	assign_walls_ew(t_cub3D *game)
{
	char	*ptr;
	int		x;
	int		y;

	ptr = game->east_wall.img;
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	ptr = game->west_wall.img;
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	if (!game->east_wall.img || !game->west_wall.img)
		return (err_message("Wall image not loaded!"));
	add_data_addr(&game->east_wall);
	add_data_addr(&game->west_wall);
	return (0);
}

//if (game->sprite_list)
int	assign_images(t_cub3D *game)
{
	if (assign_walls_ew(game) || assign_walls_ns(game) \
	|| assign_door(game) || assign_minimap(game) \
	|| assign_compass(game) || assign_sprite(game))
		return (1);
	if (make_sprite_array(game))
		return (1);
	return (0);
}
