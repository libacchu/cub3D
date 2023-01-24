/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:29:47 by obibby            #+#    #+#             */
/*   Updated: 2023/01/24 11:39:59 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	actuate_movement(t_cub3D *game)
{
	if (game->up_key)
		move_player(game, game->player.dir_y, game->player.dir_x, 1);
	if (game->down_key)
		move_player(game, game->player.dir_y, game->player.dir_x, -1);
	if (game->left_key)
		move_player(game, game->player.view_y, game->player.view_x, -1);
	if (game->right_key)
		move_player(game, game->player.view_y, game->player.view_x, 1);
}

void	put_minimap(t_cub3D *game)
{
	int	x;

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
		get_hit(game);
		line_algo(game, game->player.pos_x * 34, game->player.pos_y * 34);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->minimap.img,
		game->half_width - 10 - game->player.pos_x * 34, game->half_height
		- 10 - game->player.pos_y * 34);
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
		side = get_hit(game);
		get_perp_wall_dist(game, side);
		get_draw_coords(game);
		get_tex_pos(game, side);
		img = set_image_ptr(game, side);
		draw_to_image(game, x, img);
		game->ray.zbuffer[x] = game->ray.perp_wall_dist;
	}
	draw_sprites(game);
	put_images_to_window(game);
}

int	render(t_cub3D *game)
{
	actuate_movement(game);
	if (!game->tab)
		raycast(game);
	else
		put_minimap(game);
	inc_anims(game);
	return (0);
}
