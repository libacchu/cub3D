/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:29:47 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 14:32:04 by obibby           ###   ########.fr       */
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
		printf("playX: %f, playY: %f\n", game->player.posX, game->player.posY);
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
				ft_swap(&sprite_distance[x], &sprite_distance[y],
					&sprite_order[x], &sprite_order[y]);
			y++;
		}
		x++;
	}
}

void	move_sprite(t_cub3D *game, int *sprite_order, int i)
{
	if (ft_abs(game->player.posX - game->sprite_arr[i]->x) < 2
		&& ft_abs(game->player.posY - game->sprite_arr[i]->y) < 2)
	{
		if (!game->sprite_arr[i]->sprite_scare)
		{
			game->sprite_arr[i]->sp_anime = 2;
			game->sprite_arr[i]->sp_img = 0;
			game->sprite_arr[i]->sprite_scare = 1;
			if (!fork())
			{
				system("afplay sound/scream.mp3");
				exit(0);
			}
		}
		game->sprite_arr[sprite_order[i]]->x += 0.2
			* (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
		game->sprite_arr[sprite_order[i]]->y += 0.2
			* (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
	}
	game->sprite_arr[sprite_order[i]]->x += 0.005
		* (game->player.posX - game->sprite_arr[sprite_order[i]]->x);
	game->sprite_arr[sprite_order[i]]->y += 0.005
		* (game->player.posY - game->sprite_arr[sprite_order[i]]->y);
}

int	get_sprite_dist(t_cub3D *game)
{
	int	i;

	game->sprite_order = ft_calloc(game->sprite_total, sizeof(int));
	if (!game->sprite_order)
		return (err_message("Memory allocation failed."));
	game->sprite_distance = ft_calloc(game->sprite_total, sizeof(int));
	if (!game->sprite_distance)
		return (err_message("Memory allocation failed."));
	i = 0;
	while (game->sprite_arr[i])
	{
		game->sprite_order[i] = i;
		game->sprite_distance[i] = ((game->player.posX - game->sprite_arr[i]->x)
				* (game->player.posX - game->sprite_arr[i]->x)
				+ (game->player.posY - game->sprite_arr[i]->y)
				* (game->player.posY - game->sprite_arr[i]->y));
		i++;
	}
	sort_sprites(game->sprite_order, game->sprite_distance, game->sprite_total);
	free(game->sprite_distance);
	return (0);
}

void	get_sprite_coords(t_cub3D *game, t_sprite_cast *info)
{
	info->draw_start_y = -info->s_height / 2 + game->window_height / 2;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->s_height / 2 + game->window_height / 2;
	if (info->draw_end_y >= game->window_height)
		info->draw_end_y = game->window_height - 1;
	info->draw_start_x = -info->s_width / 2 + info->s_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->s_width / 2 + info->s_screen_x;
	if (info->draw_end_x >= game->window_width)
		info->draw_end_x = game->window_width - 1;
}

void	get_sprite_size(t_cub3D *game, t_sprite_cast *info, int i)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	trans_x;

	sprite_x = game->sprite_arr[game->sprite_order[i]]->x - game->player.posX;
	sprite_y = game->sprite_arr[game->sprite_order[i]]->y - game->player.posY;
	inv_det = 1.0 / (game->player.viewX * game->player.dirY
			- game->player.dirX * game->player.viewY);
	trans_x = inv_det * (game->player.dirY * sprite_x
			- game->player.dirX * sprite_y);
	info->trans_y = inv_det * (-game->player.viewY * sprite_x
			+ game->player.viewX * sprite_y);
	info->s_screen_x = (int)(game->half_width * (1 + trans_x / info->trans_y));
	info->s_height = abs((int)(game->window_height / info->trans_y));
	info->s_width = abs((int)(game->window_height / info->trans_y));
}

int	draw_sprites(t_cub3D *game)
{
	int			i;

	if (get_sprite_dist(game))
		return (1);
	i = -1;
	while (++i < game->sprite_total)
	{
		t_sprite_cast info;
		int		x;
		int		tex_x;
		int		y;
		int		tex_y;
		int		d;
		int		colour;

		if (!game->sprite_arr[game->sprite_order[i]]->sprite_active)
			continue ;
		move_sprite(game, game->sprite_order, i);
		get_sprite_size(game, &info, i);
		get_sprite_coords(game, &info);
		x = info.draw_start_x - 1;
		while (++x < info.draw_end_x)
		{
			tex_x = (int)(256 * (x - (-info.s_width / 2 + info.s_screen_x)) * RESOLUTION / info.s_width / 256);
			if (info.trans_y > 0 && x > 0 && x < game->window_width && info.trans_y < game->ray.zbuffer[x])
			{
				y = info.draw_start_y - 1;
				while (++y < info.draw_end_y)
				{
					d = y * 256 - game->window_height * 128 + info.s_height * 128;
					tex_y = ((d * RESOLUTION) / info.s_height) / 256;
					colour = *(int *)(game->sprite[game->sprite_arr[game->sprite_order[i]]->sp_anime].addr + ((tex_y / 8) % 64) * game->sprite[game->sprite_arr[game->sprite_order[i]]->sp_anime].line_size
							+ (((tex_x / 8) % 64) + 64 * game->sprite_arr[game->sprite_order[i]]->sp_img) * (game->sprite[game->sprite_arr[game->sprite_order[i]]->sp_anime].bpp / 8));
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
	if (game->current_time - game->last_time >= 150)
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
		draw_sprites(game);
		put_images_to_window(game);
	}
	else
		put_minimap(game);
	inc_anims(game);
	return (0);
}
