/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:29:47 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 16:02:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_minimap(t_cub3D *game)
{
	int	x;
	int	side;

	if (!game->once)
	{
		mlx_clear_window(game->mlx, game->window);
		game->once = 1;
	}
	refresh_minimap(game);
	x = -1;
	while (++x < 2305)
	{
		init_ray(game, x);
		get_delta_dist(game);
		get_side_dist(game);
		get_hit(game, &side);
		line_algo(game, game->player.posX * 34, game->player.posY * 34);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->minimap.img,
		game->half_width - 10 - game->player.posX * 34, game->half_height
		- 10 - game->player.posY * 34);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap_player.img,
		game->half_width - 8, game->half_height - 10);
}

void	raycast(t_cub3D *game)
{
	int		side;
	t_image	*img;
	int		x;

	x = -1;
	init_compass(game);
	while (++x < game->window_width)
	{
		init_ray(game, x);
		get_delta_dist(game);
		get_side_dist(game);
		get_hit(game, &side);
		get_perp_wall_dist(game, side);
		get_draw_coords(game);
		get_tex_pos(game, side);
		img = set_image_ptr(game, side);
		draw_to_image(game, x, img);
		game->ray.zbuffer[x] = game->ray.perpWallDist;
	}
	draw_sprites(game);
	put_images_to_window(game);
}

int	render(t_cub3D *game)
{
	if (!game->tab)
		raycast(game);
	else
		put_minimap(game);
	inc_anims(game);
	return (0);
}
