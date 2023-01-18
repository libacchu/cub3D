/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/17 20:39:42 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	start_loop(t_cub3D *game)
{
	mlx_mouse_hide(game->mlx, game->window);
	//mlx_do_key_autorepeaton(game->mlx);
	mlx_loop_hook(game->mlx, raycast, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_cub3D	game;

	init_game(&game);
	if (argc != 2)
		return (err_message("Try: ./cub3D maps/<map name>"));
	if (errorcheck(argv, &game))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (err_message("Failed to initialise mlx."));
	set_screen_size(&game);
	if (assign_images(&game))
		return (1);
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
