/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 10:42:33 by libacchu         ###   ########.fr       */
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
	/* init all variables & mlx_init, mlx_new_window */
	/* mlx_hook */
	/* mlx_expose_hook */
	/* mlx_key_hook */
	/* mlx_loop */
	return (0);
}
