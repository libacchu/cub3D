/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/12 21:03:46 by obibby           ###   ########.fr       */
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
	game->path = NULL;
	game->map_arr = NULL;
	
	game->player.direct = 0;
	game->player.posX = 0;
	game->player.posY = 0;

	game->ray.moveX = 0;
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
	
	x = -1;
	while (++x < 1920)
	{
		hit = 0;
		game->player.viewX = 0;
		game->player.viewY = 0.66;
		game->ray.cameraX = 2 * x / (double)1920 - 1;
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
		game->ray.lineHeight = 1080 / game->ray.perpWallDist;
		game->ray.drawStart = -game->ray.lineHeight / 2 + 1080 / 2;
		if (game->ray.drawStart < 0)
			game->ray.drawStart = 0;
		game->ray.drawEnd = game->ray.lineHeight / 2 + 1080 / 2;
		if (game->ray.drawEnd >= 1080)
			game->ray.drawEnd = 1080 - 1;
		int y;
		y = 0;
		double wallX;
		if (!side)
			wallX = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
		else
			wallX = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
		printf("wall: %f, playposY %f, playposX %f, perpWallDist: %f, rayDirY %f, rayDirX %f\n", wallX, game->player.posY, game->player.posX, game->ray.perpWallDist, game->ray.rayDirY, game->ray.rayDirX);
		wallX -= floor(wallX);
		printf("wall: %f, playposY %f, playposX %f, perpWallDist: %f, rayDirY %f, rayDirX %f\n", wallX, game->player.posY, game->player.posX, game->ray.perpWallDist, game->ray.rayDirY, game->ray.rayDirX);
		game->ray.texX = (int)(wallX * (double)64);
		if (side == 0 && game->ray.rayDirX > 0)
			game->ray.texX = 64 - game->ray.texX - 1;
		else if (side == 1 && game->ray.rayDirY < 0)
			game->ray.texX = 64 - game->ray.texX - 1;
		double step;
		step = 1.0 * 64.0 / game->ray.lineHeight;
		double texPos;
		texPos = (game->ray.drawStart - 1080 / 2 + game->ray.lineHeight / 2) * step;
		while (y < 1080)
		{
			if (y < game->ray.drawStart)
				mlx_pixel_put(game->mlx, game->window, x, y++, game->ceiling);
			else if (y > game->ray.drawEnd)
				mlx_pixel_put(game->mlx, game->window, x, y++, game->floor);
			else
			{
				game->ray.texY = (int)texPos & (64 - 1);
				texPos += step;
				int colour;
				colour = *(int *)(game->east_wall.addr + game->ray.texY % 64 * game->east_wall.line_size + game->ray.texX % 64 * (game->east_wall.bpp / 8));
				mlx_pixel_put(game->mlx, game->window, x, y++, colour);
			}
		}
	}
	return (0);
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
	while (++i < 16)
	{
		if (1 & (game.ceiling >> i))
			printf("%d\n", 1);
		else
			printf("%d\n", 0);
	}
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
	temp_raytracing_func(&game);
	//make_minimap(&game);
	mlx_hook(game.window, 17, 0, ft_mouse, &game);
	mlx_expose_hook(game.window, temp_raytracing_func, &game);
	mlx_key_hook(game.window, ft_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
