/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/14 13:44:25 by libacchu         ###   ########.fr       */
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
	game->north_wall.img = NULL;
	game->south_wall.img = NULL;
	game->west_wall.img = NULL;
	game->east_wall.img = NULL;

	game->ceiling = 0;
	game->floor = 0;
	game->compass = colourshift(200, 90, 120, 150);
	game->dark = colourshift(0, 25, 25, 25);
	game->path = NULL;
	game->map_arr = NULL;
	game->map_gen = 0;

	game->player.direct = 0;
	game->player.posX = 0;
	game->player.posY = 0;

	game->tab = 0;
	game->shift = 0;
}

int	assign_images(t_cub3D *game)
{
	char *ptr;
	int x;
	int y;

	ptr = game->north_wall.img;
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img, &game->north_wall.bpp, &game->north_wall.line_size, &game->north_wall.endian);
	free(ptr);
	ptr = game->east_wall.img;
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img, &game->east_wall.bpp, &game->east_wall.line_size, &game->east_wall.endian);
	free(ptr);
	ptr = game->west_wall.img;
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img, &game->west_wall.bpp, &game->west_wall.line_size, &game->west_wall.endian);
	free(ptr);
	ptr = game->south_wall.img;
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, ptr, &x, &y);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img, &game->south_wall.bpp, &game->south_wall.line_size, &game->south_wall.endian);
	free(ptr);
	game->minimap_wall.img = mlx_xpm_file_to_image(game->mlx, "./texture/whiteb.xpm", &x, &y);
	game->minimap_wall.addr = mlx_get_data_addr(game->minimap_wall.img, &game->minimap_wall.bpp, &game->minimap_wall.line_size, &game->minimap_wall.endian);
	game->minimap_floor.img = mlx_xpm_file_to_image(game->mlx, "./texture/blackb.xpm", &x, &y);
	game->minimap_floor.addr = mlx_get_data_addr(game->minimap_floor.img, &game->minimap_floor.bpp, &game->minimap_floor.line_size, &game->minimap_floor.endian);
	return (0);
}

void make_minimap(t_cub3D *game)
{
	int y;
	int x;

	y = -1;
	if (!game->map_gen)
	{
		while (game->map_arr[++y])
		{
			x = -1;
			while (game->map_arr[y][++x])
			{
				if (game->map_arr[y][x] == '1' || game->map_arr[y][x] == ' ')
					mlx_put_image_to_window(game->mlx, game->window, game->minimap_wall.img, x * 34, y * 34);
				else
					mlx_put_image_to_window(game->mlx, game->window, game->minimap_floor.img, x * 34, y * 34);
			}
		}
		game->map_gen = 1;
	}
	mlx_pixel_put(game->mlx, game->window, (game->player.posX) * 34, (game->player.posY) * 34, game->ceiling);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_size + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

double ft_abs(double x)
{
	if (x < 0)
		x = -x;
	return (x);
}

int temp_raytracing_func(t_cub3D *game)
{
	int x;
	int hit;
	int	side;
	// int n_coordx;
	// int n_coordy;

	x = -1;
	if (!game->tab)
	{
		while (++x < game->window_width)
		{
			hit = 0;
			game->ray.cameraX = 2 * x / (double)game->window_width - 1;
			game->ray.rayDirX = game->player.dirX + game->player.viewX * game->ray.cameraX;
			game->ray.rayDirY = game->player.dirY + game->player.viewY * game->ray.cameraX;
			game->ray.mapX = (int)game->player.posX;
			game->ray.mapY = (int)game->player.posY;
			if (!game->ray.rayDirY)
				game->ray.deltaDistY = 1e30;
			else
				game->ray.deltaDistY = ft_abs(1 / game->ray.rayDirY);
			if (!game->ray.rayDirX)
				game->ray.deltaDistX = 1e30;
			else
				game->ray.deltaDistX = ft_abs(1 / game->ray.rayDirX);
			if (game->ray.rayDirX < 0)
			{
				game->ray.stepX = -1;
				game->ray.sideDistX = (game->player.posX - game->ray.mapX) * game->ray.deltaDistX;
			}
			else
			{
				game->ray.stepX = 1;
				game->ray.sideDistX = (game->ray.mapX + 1.0 - game->player.posX) * game->ray.deltaDistX;
			}
			if (game->ray.rayDirY < 0)
			{
				game->ray.stepY = -1;
				game->ray.sideDistY = (game->player.posY - game->ray.mapY) * game->ray.deltaDistY;
			}
			else
			{
				game->ray.stepY = 1;
				game->ray.sideDistY = (game->ray.mapY + 1.0 - game->player.posY) * game->ray.deltaDistY;
			}
			while (!hit)
			{
				if (game->ray.sideDistX < game->ray.sideDistY)
				{
					game->ray.sideDistX += game->ray.deltaDistX;
					game->ray.mapX += game->ray.stepX;
					side = 0;
				}
				else
				{
					game->ray.sideDistY += game->ray.deltaDistY;
					game->ray.mapY += game->ray.stepY;
					side = 1;
				}
				if (game->map_arr[game->ray.mapY][game->ray.mapX] == '1')
					hit = 1;
			}
			if (!side)
				game->ray.perpWallDist = (game->ray.sideDistX - game->ray.deltaDistX);
			else
				game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);
			game->ray.lineHeight = game->window_height / game->ray.perpWallDist;
			game->ray.drawStart = -game->ray.lineHeight / 2 + game->window_height / 2;
			if (game->ray.drawStart < 0)
				game->ray.drawStart = 0;
			game->ray.drawEnd = game->ray.lineHeight / 2 + game->window_height / 2;
			if (game->ray.drawEnd >= game->window_height)
				game->ray.drawEnd = game->window_height - 1;
			double wallX;
			if (!side)
				wallX = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
			else
				wallX = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
			// printf("wall: %f, playposY %f, playposX %f, perpWallDist: %f, rayDirY %f, rayDirX %f\n", wallX, game->player.posY, game->player.posX, game->ray.perpWallDist, game->ray.rayDirY, game->ray.rayDirX);
			wallX -= floor(wallX);
			game->ray.texX = (int)(wallX * (double)RESOLUTION);
			if (side == 0 && game->ray.rayDirX > 0)
				game->ray.texX = RESOLUTION - game->ray.texX - 1;
			else if (side == 1 && game->ray.rayDirY < 0)
				game->ray.texX = RESOLUTION - game->ray.texX - 1;
			double step;
			step = 1.0 * RESOLUTION / game->ray.lineHeight;
			double texPos;
			texPos = (game->ray.drawStart - game->window_height / 2 + game->ray.lineHeight / 2) * step;
			t_image *img;
			if (side == 0 && game->ray.rayDirX > 0)
				img = &game->east_wall;
			else if (side == 0)
				img = &game->west_wall;
			else if (side == 1 && game->ray.rayDirY > 0)
				img = &game->south_wall;
			else
				img = &game->north_wall;
			int y;
			y = -1;
			while (++y < game->window_height)
			{
				if (y > game->y_down_limit / 3 && y < game->y_down_limit / 2 && x > game->x_left_limit && x < game->x_right_limit)
					my_mlx_pixel_put(&game->img, x, y, game->compass);
				else if (y < game->ray.drawStart)
					my_mlx_pixel_put(&game->img, x, y, game->ceiling);
				else if (y > game->ray.drawEnd)
					my_mlx_pixel_put(&game->img, x, y, game->floor);
				else
				{
					game->ray.texY = (int)texPos & (RESOLUTION - 1);
					texPos += step;
					int colour;
					colour = *(int *)(img->addr + game->ray.texY % RESOLUTION * img->line_size + game->ray.texX % RESOLUTION * (img->bpp / 8));
					my_mlx_pixel_put(&game->img, x, y, colour);
				}
			}
			// if (game->ray.rayDirX > 0.99 && game->ray.rayDirX < 1.01)
			// {
			// 	n_coordx = x;
			// 	n_coordy = y;
			// }
		}
		mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
		// mlx_put_image_to_window(game->mlx, game->window, game->north_compass.img, n_coordx, n_coordy);
	}
	else
		make_minimap(game);
	usleep(1000);
	return (0);
}

int	mouse_move(int x, int y, t_cub3D *game)
{
	int x_dif;
	double old_X;
	
	mlx_mouse_get_pos(game->mlx, game->window, &x, &y);
	x_dif = x - game->mouse_prev_x;
	game->mouse_prev_x = x;
	game->mouse_prev_y = y;
	if (x_dif < 0)
	{
		while (x_dif++ < 0)
		{
			old_X = game->player.dirX;
			game->player.dirX = old_X * cos(-MOUSE_SPEED) - game->player.dirY * sin(-MOUSE_SPEED);
			game->player.dirY = old_X * sin(-MOUSE_SPEED) + game->player.dirY * cos(-MOUSE_SPEED);
			old_X = game->player.viewX;
			game->player.viewX = old_X * cos(-MOUSE_SPEED) - game->player.viewY * sin(-MOUSE_SPEED);
			game->player.viewY = old_X * sin(-MOUSE_SPEED) + game->player.viewY * cos(-MOUSE_SPEED);
		}
	}
	else if (x_dif > 0)
	{
		while (x_dif-- > 0)
		{
			old_X = game->player.dirX;
			game->player.dirX = old_X * cos(MOUSE_SPEED) - game->player.dirY * sin(MOUSE_SPEED);
			game->player.dirY = old_X * sin(MOUSE_SPEED) + game->player.dirY * cos(MOUSE_SPEED);
			old_X = game->player.viewX;
			game->player.viewX = old_X * cos(MOUSE_SPEED) - game->player.viewY * sin(MOUSE_SPEED);
			game->player.viewY = old_X * sin(MOUSE_SPEED) + game->player.viewY * cos(MOUSE_SPEED);
		}
	}
	if (game->mouse_prev_x > game->x_right_limit || game->mouse_prev_x < game->x_left_limit || game->mouse_prev_y > game->y_up_limit || game->mouse_prev_y < game->y_down_limit)
	{
		game->mouse_prev_x = game->half_width;
		game->mouse_prev_y = game->half_height;
		mlx_mouse_move(game->mlx, game->window, game->half_width, game->half_height);	
	}
	return (0);
}

void	start_loop(t_cub3D *game)
{
	mlx_do_sync(game->mlx);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_loop_hook(game->mlx, temp_raytracing_func, game);
	mlx_loop(game->mlx);
}

void print_map_array(t_cub3D *game)
{
	int i;
	i = -1;
	while (game->map_arr[++i])
	{
		printf("%s\n", game->map_arr[i]);	
	}
}

void	set_screen_size(t_cub3D *game)
{
	mlx_get_screen_size(game->mlx, &game->window_width, &game->window_height);
	if (game->window_width > 1920)
		game->window_width = 1920;
	if (game->window_height > 1080)
		game->window_height = 1080;
	game->half_height = game->window_height / 2;
	game->half_width = game->window_width / 2;
	game->mouse_prev_x = game->half_width;
	game->mouse_prev_y = game->half_height;
	game->x_left_limit = game->window_width / 15;
	game->x_right_limit = game->window_width * 14 / 15;
	game->y_up_limit = game->window_height * 14 / 15;
	game->y_down_limit = game->window_height / 15;
	game->img.img = mlx_new_image(game->mlx, game->window_width, game->window_height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_size, &game->img.endian);
}

int	main(int argc, char **argv)
{
	t_cub3D game;
	init_game(&game);
	if (argc != 2)
		return (err_message("Try: ./cub3D maps/<map name>"));
	if (errorcheck(argv, &game))
		return (1);
	print_map_array(&game); // for debugging
	game.mlx = mlx_init();
	if (!game.mlx)
		return(err_message("Failed to initialise mlx."));
	set_screen_size(&game);
	if (assign_images(&game))
		return (1);
	printf("x: %d, y: %d\n", game.window_width, game.window_height);
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "cub3D");
	//temp_raytracing_func(&game);
	//make_minimap(&game);
	mlx_hook(game.window, 2, 1L << 0, ft_key, &game);
	mlx_hook(game.window, 17, 0, ft_mouse, &game);
	mlx_expose_hook(game.window, temp_raytracing_func, &game);
	//mlx_mouse_hook(game.window, mouse_move, &game);
	mlx_hook(game.window, 6, 1L << 6, mouse_move, &game);
	start_loop(&game);
	return (0);
}
