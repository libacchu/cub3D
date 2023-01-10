#include "../includes/cub3D.h"

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
