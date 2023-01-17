/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:41:04 by obibby            #+#    #+#             */
/*   Updated: 2023/01/17 15:11:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	assign_compass(t_cub3D *game)
{
	int	x;
	int	y;

	game->north_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/n.xpm", &x, &y);
	game->north_compass.addr = mlx_get_data_addr(game->north_compass.img,
			&game->north_compass.bpp, &game->north_compass.line_size,
			&game->north_compass.endian);
	game->east_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/e.xpm", &x, &y);
	game->east_compass.addr = mlx_get_data_addr(game->east_compass.img,
			&game->east_compass.bpp, &game->east_compass.line_size,
			&game->east_compass.endian);
	game->south_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/s.xpm", &x, &y);
	game->south_compass.addr = mlx_get_data_addr(game->south_compass.img,
			&game->south_compass.bpp, &game->south_compass.line_size,
			&game->south_compass.endian);
	game->west_compass.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/w.xpm", &x, &y);
	game->west_compass.addr = mlx_get_data_addr(game->west_compass.img,
			&game->west_compass.bpp, &game->west_compass.line_size,
			&game->west_compass.endian);
}

void	assign_minimap(t_cub3D *game)
{
	int	x;
	int	y;

	game->minimap_wall.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/whiteb.xpm", &x, &y);
	game->minimap_wall.addr = mlx_get_data_addr(game->minimap_wall.img,
			&game->minimap_wall.bpp, &game->minimap_wall.line_size,
			&game->minimap_wall.endian);
	game->minimap_floor.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/blackb.xpm", &x, &y);
	game->minimap_floor.addr = mlx_get_data_addr(game->minimap_floor.img,
			&game->minimap_floor.bpp, &game->minimap_floor.line_size,
			&game->minimap_floor.endian);
	game->minimap_player.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/gui.xpm", &x, &y);
	game->minimap_player.addr = mlx_get_data_addr(game->minimap_player.img,
			&game->minimap_player.bpp, &game->minimap_player.line_size,
			&game->minimap_player.endian);
}

void	assign_walls_ns(t_cub3D *game)
{
	char	*ptr;
	int		x;
	int		y;

	ptr = game->north_wall.img;
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img,
			&game->north_wall.bpp, &game->north_wall.line_size,
			&game->north_wall.endian);
	free(ptr);
	ptr = game->south_wall.img;
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img,
			&game->south_wall.bpp, &game->south_wall.line_size,
			&game->south_wall.endian);
	free(ptr);
}

void	assign_walls_ew(t_cub3D *game)
{
	char	*ptr;
	int		x;
	int		y;

	ptr = game->east_wall.img;
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img,
			&game->east_wall.bpp, &game->east_wall.line_size,
			&game->east_wall.endian);
	free(ptr);
	ptr = game->west_wall.img;
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img,
			&game->west_wall.bpp, &game->west_wall.line_size,
			&game->west_wall.endian);
	free(ptr);
}

int	make_sprite_array(t_cub3D *game)
{
	t_sprite	*node;
	t_sprite	*prev;
	int			i;

	node = game->sprite_list;
	game->sprite_arr = ft_calloc(game->sprite_total + 1, sizeof(t_sprite *));
	if (!game->sprite_arr)
		return (err_message("Memory allocation failed."));
	i = 0;
	while (node)
	{
		game->sprite_arr[i] = ft_calloc(1, sizeof(t_sprite));
		game->sprite_arr[i]->x = node->x;
		game->sprite_arr[i]->y = node->y;
		game->sprite_arr[i]->sp_anime = 0;
		game->sprite_arr[i]->sp_img = 0;
		game->sprite_arr[i]->sp_img_total[0] = 6;
		game->sprite_arr[i]->sp_img_total[1] = 7;
		game->sprite_arr[i]->sp_img_total[2] = 4;
		game->sprite_arr[i]->sp_img_total[3] = 7;
		game->sprite_arr[i]->sprite_active = 0;
		game->sprite_arr[i]->sprite_deactivate = 0;
		prev = node;
		node = node->next;
		free(prev);
		i++;
	}
	return (0);
}

int	assign_images(t_cub3D *game)
{
	assign_walls_ns(game);
	assign_walls_ew(game);
	assign_door(game);
	assign_minimap(game);
	assign_compass(game);
	//if (game->sprite_list)
	assign_sprite(game);
	if (make_sprite_array(game))
		return (1);
	return (0);
}
