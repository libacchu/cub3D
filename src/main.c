/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 14:54:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
	TODO:
	- make struct
	- error checks
		- argv
		- map path
		- valid map
			- NO and path to img
			- SO
			- WE
			- EA
			- F and RGB
			- C 
			
			Map: only have 6 possible characters
				- 0: for an empty space
				- 1: for a wall
				- N,S,E or W:  player’s start position and spawning orientation.
			-errorMessages
			
	- create mlx hooks
	- Window management

		
*/

// checks map file for valid NO, SO, WE, and EA images, valid rgb values for c and f, and valid map.

void init_game(t_cub3D *game)
{
	game->north_wall = NULL;
	game->south_wall = NULL;
	game->west_wall = NULL;
	game->east_wall = NULL;
	game->ceiling = 0;
	game->floor = 0;
	game->path = NULL;
	game->map_arr = NULL;
	
	game->player.direct = 0;
	game->player.x = 0;
	game->player.y = 0;
}

int	assign_images(t_cub3D *game)
{
	char *ptr;
	int x;
	int y;

	ptr = game->north_wall;
	game->north_wall = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	ptr = game->east_wall;
	game->east_wall = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	ptr = game->west_wall;
	game->west_wall = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	ptr = game->south_wall;
	game->south_wall = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	free(ptr);
	game->minimap_wall = mlx_xpm_file_to_image(game->mlx, "./texture/whiteb.xpm", &x, &y);
	game->minimap_floor = mlx_xpm_file_to_image(game->mlx, "./texture/blackb.xpm", &x, &y);
	return (0);
}

void make_minimap(t_cub3D *game)
{
	int y;
	int x;

	y = -1;
	while (game->map_arr[++y])
	{
		x = -1;
		while (game->map_arr[y][++x])
		{
			if (game->map_arr[y][x] == '1' || game->map_arr[y][x] == ' ')
				mlx_put_image_to_window(game->mlx, game->window, game->minimap_wall, y * 34, x * 34);
			else
				mlx_put_image_to_window(game->mlx, game->window, game->minimap_floor, y * 34, x * 34);
		}
	}
}

int	main(int argc, char **argv)
{
	t_cub3D game;
	
	init_game(&game);
	if (argc != 2)
		return (err_message("Try: ./cub3D map/<map name>"));
	if (errorcheck(argv, &game))
		return (1);
	int i;

	i = -1;
	while (game.map_arr[++i])
	{
		printf("%s\n", game.map_arr[i]);	
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		return(err_message("Failed to initialise mlx."));
	if (assign_images(&game))
		return (1);
	game.window = mlx_new_window(game.mlx, 1920, 1080, "cub3D");
	make_minimap(&game);
	mlx_hook(game.window, 17, 0, ft_mouse, &game);
	//mlx_expose_hook(game.window, render_frame, &g);
	mlx_key_hook(game.window, ft_key, &game);
	/* mlx_expose_hook */
	mlx_loop(game.mlx);
	return (0);
}
