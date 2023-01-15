/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/15 01:46:26 by obibby           ###   ########.fr       */
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

// checks map file for valid NO, SO, WE, and EA images, 
// valid rgb values for c and f, and valid map.

void	start_loop(t_cub3D *game)
{
	//mlx_do_sync(game->mlx);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_loop_hook(game->mlx, raycast, game);
	mlx_loop(game->mlx);
}

void	print_map_array(t_cub3D *game)
{
	int	i;

	i = -1;
	while (game->map_arr[++i])
		printf("%s\n", game->map_arr[i]);
}

int	main(int argc, char **argv)
{
	t_cub3D	game;

	init_game(&game);
	if (argc != 2)
		return (err_message("Try: ./cub3D maps/<map name>"));
	if (errorcheck(argv, &game))
		return (1);
	print_map_array(&game); // for debugging
	game.mlx = mlx_init();
	if (!game.mlx)
		return (err_message("Failed to initialise mlx."));
	set_screen_size(&game);
	if (assign_images(&game))
		return (1);
	printf("x: %d, y: %d\n", game.window_width, game.window_height);
	game.window = mlx_new_window(game.mlx, game.window_width,
			game.window_height, "cub3D");
	make_minimap(&game);
	mlx_hook(game.window, 2, 1L << 0, ft_key, &game);
	mlx_hook(game.window, 17, 0, ft_mouse, &game);
	mlx_expose_hook(game.window, raycast, &game);
	mlx_hook(game.window, 6, 1L << 6, mouse_move, &game);
	start_loop(&game);
	return (0);
}
