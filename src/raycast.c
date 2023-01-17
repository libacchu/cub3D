/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:29:47 by obibby            #+#    #+#             */
/*   Updated: 2023/01/17 18:04:48 by obibby           ###   ########.fr       */
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
	while (++x < game->minimap_size_x)
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

void	sort_sprites(int *sprite_order, int *sprite_distance, int total_sprites)
{
	int	x;
	int	y;

	x = 0;
	while (x < total_sprites)
	{
		y = x + 1;
		while (y < total_sprites)
		{
			if (sprite_distance[y] > sprite_distance[x])
				ft_swap(&sprite_distance[x], &sprite_distance[y], &sprite_order[x], &sprite_order[y]);
			y++;
		}
		x++;
	}
}

void	move_sprite(t_cub3D *game, int *sprite_order, int i)
{
	
	if (ft_abs(game->player.posX - game->sprite_arr[i]->x) < 2 && ft_abs(game->player.posY - game->sprite_arr[i]->y) < 2)
	{
		if (!game->sprite_arr[i]->sprite_scare)
		{
			game->sprite_arr[i]->sp_anime = 2;
			game->sprite_arr[i]->sp_img = 0;
			game->sprite_arr[i]->sprite_scare = 1;
			if (!fork())
			{
				system("afplay sound/sample-3s.mp3");
				exit(0);
			}
		}
		game->sprite_arr[sprite_order[i]]->x += 0.2 * (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
		game->sprite_arr[sprite_order[i]]->y += 0.2 * (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
	}
	game->sprite_arr[sprite_order[i]]->x += 0.005 * (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
	game->sprite_arr[sprite_order[i]]->y += 0.005 * (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
}

int	do_stuff_to_sprites(t_cub3D *game)
{
	int			*sprite_order;
	int			*sprite_distance;
	int			i;

	sprite_order = ft_calloc(game->sprite_total, sizeof(int));
	if (!sprite_order)
		return (err_message("Memory allocation failed."));
	sprite_distance = ft_calloc(game->sprite_total, sizeof(int));
	if (!sprite_distance)
		return (err_message("Memory allocation failed."));
	i = 0;
	while (game->sprite_arr[i])
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((game->player.posX - game->sprite_arr[i]->x) * (game->player.posX - game->sprite_arr[i]->x) + (game->player.posY - game->sprite_arr[i]->y) * (game->player.posY - game->sprite_arr[i]->y));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, game->sprite_total);
	i = -1;
	while (++i < game->sprite_total)
	{
		double	sprite_x;
		double	sprite_y;
		double	inv_det;
		double	trans_x;
		double	trans_y;
		int		s_screen_x;
		int		s_height;
		int		draw_start_y;
		int		draw_end_y;
		int		s_width;
		int		draw_start_x;
		int		draw_end_x;
		int		x;
		int		tex_x;
		int		y;
		int		tex_y;
		int		d;
		int		colour;

		if (!game->sprite_arr[sprite_order[i]]->sprite_active)
			continue ;
		sprite_x = game->sprite_arr[sprite_order[i]]->x - game->player.posX;
		sprite_y = game->sprite_arr[sprite_order[i]]->y - game->player.posY;
		move_sprite(game, sprite_order, i);
		inv_det = 1.0 / (game->player.viewX * game->player.dirY - game->player.dirX * game->player.viewY);
		trans_x = inv_det * (game->player.dirY * sprite_x - game->player.dirX * sprite_y);
		trans_y = inv_det * (-game->player.viewY * sprite_x + game->player.viewX * sprite_y);
		s_screen_x = (int)(game->half_width * (1 + trans_x / trans_y));
		s_height = abs((int)(game->window_height / trans_y));
		// height of sprite on screen
		draw_start_y = -s_height / 2 + game->window_height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = s_height / 2 + game->window_height / 2;
		if (draw_end_y >= game->window_height)
			draw_end_y = game->window_height - 1;
		// width of sprite on screen
		s_width = abs((int)(game->window_height / trans_y));
		draw_start_x = -s_width / 2 + s_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = s_width / 2 + s_screen_x;
		if (draw_end_x >= game->window_width)
			draw_end_x = game->window_width - 1;
		x = draw_start_x - 1;
		while (++x < draw_end_x)
		{
			tex_x = (int)(256 * (x - (-s_width / 2 + s_screen_x)) * RESOLUTION / s_width / 256);
			if (trans_y > 0 && x > 0 && x < game->window_width && trans_y < game->ray.zbuffer[x])
			{
				y = draw_start_y - 1;
				while (++y < draw_end_y)
				{
					d = y * 256 - game->window_height * 128 + s_height * 128;
					tex_y = ((d * RESOLUTION) / s_height) / 256;
					colour = *(int *)(game->sprite[game->sprite_arr[sprite_order[i]]->sp_anime].addr + ((tex_y / 8) % 64) * game->sprite[game->sprite_arr[sprite_order[i]]->sp_anime].line_size
							+ (((tex_x / 8) % 64) + 64 * game->sprite_arr[sprite_order[i]]->sp_img) * (game->sprite[game->sprite_arr[sprite_order[i]]->sp_anime].bpp / 8));
					if ((colour & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&game->img, x, y, colour);
				}
			}
		}
	}
	return (0);
}

void	inc_anims(t_cub3D *game)
{
	int	i;

	i = -1;
	game->current_time = get_time_in_ms();
	if (get_time_in_ms() - game->last_time >= 150)
	{
		while (game->sprite_arr[++i])
		{
			game->sprite_arr[i]->sp_img++;
			if (game->sprite_arr[i]->sprite_scare)
			{
				if (game->sprite_arr[i]->sp_img > 3)
					game->sprite_arr[i]->sp_img = 2;
			}
			else if (game->sprite_arr[i]->sp_anime == 2)
			{
				game->sprite_arr[i]->sp_img -= 2;
				if (game->sprite_arr[i]->sp_img < 0)
				{
					game->sprite_arr[i]->sp_anime = 1;
					game->sprite_arr[i]->sp_img = 0;
				}
			}
			else if (game->sprite_arr[i]->sprite_activate)
			{
				if (game->sprite_arr[i]->sprite_activate == 1)
				{
					game->sprite_arr[i]->sp_anime = 0;
					game->sprite_arr[i]->sp_img = 0;
					game->sprite_arr[i]->sprite_active = 1;
				}
				if (game->sprite_arr[i]->sp_img == game->sprite_arr[i]->sp_img_total[game->sprite_arr[i]->sp_anime])
				{
					game->sprite_arr[i]->sp_anime++;
					game->sprite_arr[i]->sp_img = 0;
				}
				game->sprite_arr[i]->sprite_activate++;
				if (game->sprite_arr[i]->sprite_activate == 15)
				{
					game->sprite_arr[i]->sprite_activate = 0;
					game->sprite_arr[i]->sp_img = 0;
				}
			}
			else if (game->sprite_arr[i]->sprite_deactivate)
			{
				if (game->sprite_arr[i]->sprite_deactivate == 1)
				{
					game->sprite_arr[i]->sp_anime = 3;
					game->sprite_arr[i]->sp_img = 1;
				}
				game->sprite_arr[i]->sprite_deactivate++;
				if (game->sprite_arr[i]->sprite_deactivate == 7)
				{
					game->sprite_arr[i]->sprite_active = 0;
					game->sprite_arr[i]->sprite_deactivate = 0;
				}
			}
			else
			{
				game->sprite_arr[i]->sp_anime = 1;
				game->sprite_arr[i]->sp_img = game->sprite_arr[i]->sp_img % game->sprite_arr[i]->sp_img_total[game->sprite_arr[i]->sp_anime];
			}
		}
		game->last_time = game->current_time;
	}
	
}

int	raycast(t_cub3D *game)
{
	int		x;
	int		side;
	t_image	*img;

	x = -1;
	if (!game->tab)
	{
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
		do_stuff_to_sprites(game);
		put_images_to_window(game);
	}
	else
		put_minimap(game);
	inc_anims(game);
	return (0);
}
