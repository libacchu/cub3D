#include "../includes/cub3D.h"

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
