/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:38:43 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/15 02:08:24 by obibby           ###   ########.fr       */
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

void	free_all_imgs(t_cub3D *game)
{
	if (game->north_wall.img)
		free_img(game->mlx, game->north_wall.img);
	if (game->west_wall.img)
		free_img(game->mlx, game->west_wall.img);
	if (game->east_wall.img)
		free_img(game->mlx, game->east_wall.img);
	if (game->south_wall.img)
		free_img(game->mlx, game->south_wall.img);
	if (game->north_compass.img)
		free_img(game->mlx, game->north_compass.img);
	if (game->east_compass.img)
		free_img(game->mlx, game->east_compass.img);
	if (game->south_compass.img)
		free_img(game->mlx, game->south_compass.img);
	if (game->west_compass.img)
		free_img(game->mlx, game->west_compass.img);
	if (game->minimap_wall.img)
		free_img(game->mlx, game->minimap_wall.img);
	if (game->minimap_floor.img)
		free_img(game->mlx, game->minimap_floor.img);
	if (game->img.img)
		free_img(game->mlx, game->img.img);
}

void	ft_free(t_cub3D *game)
{
	if (game->map_arr)
		free_array(game->map_arr);
	free_all_imgs(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}
