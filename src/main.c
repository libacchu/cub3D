/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/09 13:35:02 by obibby           ###   ########.fr       */
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
			
	- create mlx hooks
	- Window management

		
*/

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
		ft_printf("Invalid file extension.\n");
		return (-1);
	}
	// check access (use open function)
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		ft_printf("File doesn't exist!\n");
		return (-1);
	}
	return (fd);
}

int check_map(char *str, t_cub3D *game)
{
	(void)str;
	(void)game;
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
		n = ft_atoi(&str[i]);
		if (n > 255 || n < 0)
			return (1);
		*colour = *colour | n;
		*colour = *colour << shift;
		while (str[i] && str[i] != ',')
			i++;
		shift -= 4;
	}
	return (0);
}

int check_tex(char *str, t_cub3D *game)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ' && str[3])
		game->north_wall = "blah";
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ' && str[3])
		game->south_wall = "blah";
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ' && str[3])
		game->west_wall = "blah";
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ' && str[3])
		game->east_wall = "blah";
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
			str = get_next_line(fd);
			continue ;
		}
		else if (i == 6)
		{
			if (check_map(str, game))
				return (1);
		}
		else if (i >= 4)
		{
			if (check_rgb(str, game))
				return (1);
			i++;
		}
		else
		{
			if (check_tex(str, game))
				return (1);
			i++;
		}
		str = get_next_line(fd);
	}
	return (0);
}

int errorcheck(char **argv, t_cub3D *game)
{
	int fd;
	
	fd = err_path_name(argv[1]);
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
