/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/10 13:49:07 by libacchu         ###   ########.fr       */
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

int not_only_white_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] > 32)
			return (1);
	}
	return (0);
}

int	create_map_arr(char *str, t_cub3D *game, int fd)
{
	int i;

	game->map_arr = ft_calloc(count_rows(game->path) + 1, sizeof(char *));
	if (!game->map_arr)
		return (err_message("Failed to allocate memory.\n"));
	i = 0;
	while (!not_only_white_space(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	while (str)
	{
		if (not_only_white_space(str))
		{
			game->map_arr[i] = ft_strtrim(str, "\n");
			if (!game->map_arr[i++])
				return (err_message("Failed to allocate memory.\n"));			
		}
		else
		{
			free(str);
			return (0);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}

int check_chars(char c)
{
	char *list;

	list = "01NSEW";
	if (ft_strchr(list, c))
		return (0);
	return (1);
}

int check_map(char *str, t_cub3D *game, int fd)
{
	int x;
	int y;

	if (create_map_arr(str, game, fd))
		return (1);
	y = -1;
	while (game->map_arr[++y])
	{
		x = -1;
		while (game->map_arr[y][++x])
		{
			if (game->map_arr[y][x] != ' ' && check_chars(game->map_arr[y][x]))
				return (err_message("Invalid character in map."));
			if (game->map_arr[y][x] != '1' && game->map_arr[y][x] > 32)
			{
				if ((x == 0 || y == 0 || !game->map_arr[y][x + 1] || !game->map_arr[y + 1]))
					return (err_message("Map is not enclosed with walls."));	
				if (check_chars(game->map_arr[y][x + 1]))
				{
					if (game->map_arr[y][x + 1] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
				if (check_chars(game->map_arr[y][x - 1]))
				{
					if (game->map_arr[y][x - 1] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
				if (check_chars(game->map_arr[y + 1][x]))
				{
					if (game->map_arr[y + 1][x] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
				if (check_chars(game->map_arr[y - 1][x]))
				{
					if (game->map_arr[y - 1][x] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
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
		if (game->north_wall)
			return (err_message("Too many textures in mapfile."));
		game->north_wall = ft_strdup(&str[3]);
		if (!game->north_wall)
			return (err_message("Memory allocation failed."));
	}
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ' && str[3])
	{
		if (game->south_wall)
			return (err_message("Too many textures in mapfile."));
		game->south_wall = ft_strdup(&str[3]);
		if (!game->south_wall)
			return (err_message("Memory allocation failed."));
	}
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ' && str[3])
	{
		if (game->west_wall)
			return (err_message("Too many textures in mapfile."));
		game->west_wall = ft_strdup(&str[3]);
		if (!game->west_wall)
			return (err_message("Memory allocation failed."));
	}
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ' && str[3])
	{
		if (game->east_wall)
			return (err_message("Too many textures in mapfile."));
		game->east_wall = ft_strdup(&str[3]);
		if (!game->east_wall)
			return (err_message("Memory allocation failed."));
	}
	else
		return (1);
	return (0);
}

// checks map file for valid NO, SO, WE, and EA images, valid rgb values for c and f, and valid map.

int	err_map(int fd, t_cub3D *game)
{
	char *str;
	int i;
	int flag;
	
	flag = 0;
	i = 0;
	str = get_next_line(fd);
	while (str && i != 6)
	{
		if (!not_only_white_space(str))
		{
			free(str);
			str = get_next_line(fd);
			continue ;
		}
		else
		{
			ft_printf(str);
			if (str[0] == 'F' || str[0] == 'C')
			{
				if (check_rgb(str, game))
					return (err_message("Invalid colour variable in map file."));
			}
			else if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3) || !ft_strncmp(str, "EA ", 3) || !ft_strncmp(str, "WE ", 3) )
			{
				if (check_tex(str, game))
					return (1);
			}
			else
				return (err_message("Invalid or missing variable in map file."));
			i++;
		}
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
		return (err_message("No map."));
	else if (i == 6 && check_map(str, game, fd))
		return (1);
	// else if (i == 6)
	// 	return (1);
	if (i == 0)
		return (err_message("Empty file."));
	if (i < 6)
		return (err_message("Invalid map file."));
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
}

int	main(int argc, char **argv)
{
	t_cub3D game;
	
	init_game(&game);
	if (argc != 2 || errorcheck(argv, &game))
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
