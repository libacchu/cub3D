/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:14:36 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/09 12:40:15 by libacchu         ###   ########.fr       */
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
	char str;
	int fd;
	int i;
	// check ending
	i = 0;
	while (path[i])
		i++;
	if (ft_strcmp(path[i - 4]), ".cub")
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

int check_tex_path(char *str, t_cub3D *game)
{
	if (str[0] == 'N' && str[1] == 'O')
	
}

int	err_map(int fd, t_cub3D *game)
{
	char *str;
	int i;
	// check N S W E image
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] == '\n')
			continue ;
		if (i >= 6)
			check_map(str, game);
		else if (i >= 4)
			check_rgb(str, game);
		else
			check_tex_path(str, game);
		str = get_next_line(fd);
	}
	// check F C RBG
	// check if map is valid
	
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
