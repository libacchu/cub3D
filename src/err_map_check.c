#include "../includes/cub3D.h"

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
			if (ft_strchr("NSEW", game->map_arr[y][x]))
			{
				if (!game->player.direct)
				{
					game->player.direct = game->map_arr[y][x];
					game->player.x = x;
					game->player.y = y;
				}
				else
					return (err_message("Invalid character: Check player elements."));
			}
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
				if ((int)ft_strlen(game->map_arr[y + 1]) < x + 1 || check_chars(game->map_arr[y + 1][x]))
				{
					if ((int)ft_strlen(game->map_arr[y + 1]) < x + 1 || game->map_arr[y + 1][x] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
				if ((int)ft_strlen(game->map_arr[y - 1]) < x + 1 || check_chars(game->map_arr[y - 1][x]))
				{
					if ((int)ft_strlen(game->map_arr[y - 1]) < x + 1 || game->map_arr[y - 1][x] == ' ')
						return (err_message("Map is not enclosed with walls."));
					return (err_message("Invalid character in map."));
				}
			}
		}
	}
	if (!game->player.direct)
		return (err_message("No player location in map."));
	return (0);
}
