/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/24 11:43:18 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	free_strings(t_cub3D *game)
{
	int			i;
	t_sprite	*temp;

	while (game->sprite_list)
	{
		temp = game->sprite_list;
		game->sprite_list = game->sprite_list->next;
		free(temp);
	}
	if (game->map_arr)
	{
		i = -1;
		while (game->map_arr[++i])
			free(game->map_arr[i]);
		free(game->map_arr);
	}
	if (game->north_wall_addr)
		free(game->north_wall_addr);
	if (game->east_wall_addr)
		free(game->east_wall_addr);
	if (game->south_wall_addr)
		free(game->south_wall_addr);
	if (game->west_wall_addr)
		free(game->west_wall_addr);
	return (1);
}

void	start_loop(t_cub3D *game)
{
	mlx_do_sync(game->mlx);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_cub3D	game;

	init_game(&game);
	if (argc != 2)
		return (err_message("Try: ./cub3D maps/<map name>"));
	if (errorcheck(argv, &game))
		return (free_strings(&game));
	game.mlx = mlx_init();
	if (!game.mlx)
		return (free_strings(&game), err_message("Failed to initialise mlx."));
	set_screen_size(&game);
	if (assign_images(&game))
		return (1);
	game.window = mlx_new_window(game.mlx, game.window_width,
			game.window_height, "cub3D");
	make_minimap(&game);
	mlx_hook(game.window, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, ft_key_release, &game);
	mlx_hook(game.window, 17, 0, ft_mouse, &game);
	mlx_expose_hook(game.window, render, &game);
	mlx_hook(game.window, 6, 1L << 6, mouse_move, &game);
	start_loop(&game);
	return (0);
}
