/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:38:43 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/19 17:01:42 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_img(void *mlx, void *ptr)
{
	if (ptr)
		mlx_destroy_image(mlx, ptr);
	ptr = NULL;
}

void	free_sprites(void *mlx, t_image *sprite)
{
	int	i;

	i = -1;
	while (++i < 4)
		free_img(mlx, sprite[i].img);
	free(sprite);
	sprite = NULL;
}

int	ft_free(t_cub3D *game)
{
	t_door	*door;

	// if (game->map_arr)
	// 	free_array(game->map_arr);
	free_all_imgs(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	while (game->door_list)
	{
		door = game->door_list;
		game->door_list = game->door_list->next;
		free(door);
	}
	return (1);
}
