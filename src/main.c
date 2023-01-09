/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/09 21:19:14 by obibby           ###   ########.fr       */
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

int err_message(char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

int err_path_name(char *path) 
{
	int fd;
	int i;
	// check ending
	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
	{
		err_message("Invalid file extension.\n");
		return (-1);
	}
	// check access (use open function)
	fd = open(path, O_RDONLY);
	if (fd == -1)
		err_message("File doesn't exist!\n");
	return (fd);
}

int count_rows(char *path)
{
	int fd;
	char *str;
	int count;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	count = 0;
	while (str)
	{
		if (str[0] != '\n')
			count++;
		free(str);
		str = get_next_line(fd);
	}
	count -= 6;
	free(str);
	return (count);
}

int	create_map_arr(char *str, t_cub3D *game, int fd)
{
	int i;

	game->x_num = count_rows(game->path);
	game->arr = ft_calloc(game->x_num + 1, sizeof(char *));
	if (!game->arr)
		return (err_message("Failed to allocate memory.\n"));
	i = 0;
	while (str)
	{
		if (str[0] != '\n')
		{
			game->arr[i] = ft_strtrim(str, "\n");
			if (!game->arr[i++])
				return (err_message("Failed to allocate memory.\n"));			
		}
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}

int check_map(char *str, t_cub3D *game, int fd)
{
	int x;
	int y;
	int len;

	if (create_map_arr(str, game, fd))
		return (1);
	y = -1;
	while (game->arr[++y])
	{
		x = -1;
		len = ft_strlen(game->arr[y]);
		while (game->arr[y][++x])
		{
			if (game->arr[y][x] != '1' && game->arr[y][x] > 32)
			{
				if ((x == 0 || y == 0 || x == len - 1 || y == game->x_num - 1))
					return (err_message("Map is not enclosed with walls."));
				if (game->arr[y][x + 1] != '1' && game->arr[y][x + 1] != '0')
					return (err_message("Map is not enclosed with walls."));
				if (game->arr[y][x - 1] != '1' && game->arr[y][x - 1] != '0')
					return (err_message("Map is not enclosed with walls."));
				if (game->arr[y + 1][x] != '1' && game->arr[y + 1][x] != '0')
					return (err_message("Map is not enclosed with walls."));
				if (game->arr[y - 1][x] != '1' && game->arr[y - 1][x] != '0')
					return (err_message("Map is not enclosed with walls."));
			}
		}
	}
	return (0);
}

int check_rgb(char *str, t_cub3D *game)
{
	int n;
	int *colour;
	int i;
	int shift;

	colour = 0;
	i = 1;
	shift = 16;
	if (str[0] == 'C')
		colour = &game->ceiling;
	else
		colour = &game->floor;
	while (shift >= 8)
	{
		while (str[i] && (str[i] <= 32 || str[i] == ','))
			i++;
		if (!str[i] || !ft_isdigit(str[i]))
			return (1);
		n = ft_atoi(&str[i]);
		if (n > 255 || n < 0)
			return (1);
		*colour = *colour | n;
		*colour = *colour << shift;
		while (str[i] && str[i] != ',')
			i++;
		i++;
		shift -= 4;
	}
	return (0);
}

int check_tex(char *str, t_cub3D *game)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ' && str[3])
	{
		game->north_wall = str;
		if (!game->north_wall)
			return (1);
	}
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ' && str[3])
		game->south_wall = str;
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ' && str[3])
		game->west_wall = str;
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ' && str[3])
		game->east_wall = str;
	else
		return (1);
	return (0);
}

// checks map file for valid NO, SO, WE, and EA images, valid rgb values for c and f, and valid map.

int	err_map(int fd, t_cub3D *game)
{
	char *str;
	int i;

	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] == '\n')
		{
			free(str);
			str = get_next_line(fd);
			continue ;
		}
		else if (i == 6)
		{
			if (check_map(str, game, fd))
				return (1);
			return (0);
		}
		else
		{
			if (str[0] == 'F' || str[0] == 'C')
			{
				if (check_rgb(str, game))
					return (err_message("Invalid statement in map file."));
			}
			else
			{
				if (check_tex(str, game))
					return (err_message("Invalid statement in map file."));
			}
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}

int errorcheck(char **argv, t_cub3D *game)
{
	int fd;
	
	game->path = argv[1];
	fd = err_path_name(game->path);
	if (fd == -1)
		return (1);
	if (err_map(fd, game))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3D game;
	if (argc != 2 || errorcheck(argv, &game))
		return (1);
	/* init all variables & mlx_init, mlx_new_window */
	/* mlx_hook */
	/* mlx_expose_hook */
	/* mlx_key_hook */
	/* mlx_loop */
	return (0);
}
