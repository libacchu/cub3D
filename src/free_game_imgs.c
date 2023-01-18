/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game_imgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:38:43 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/18 16:31:01 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_wall_imgs(t_cub3D *game)
{
	if (game->north_wall.img)
		free_img(game->mlx, game->north_wall.img);
	if (game->west_wall.img)
		free_img(game->mlx, game->west_wall.img);
	if (game->east_wall.img)
		free_img(game->mlx, game->east_wall.img);
	if (game->south_wall.img)
		free_img(game->mlx, game->south_wall.img);
	if (game->door.img)
		free_img(game->mlx, game->door.img);
}

void	free_compass_imgs(t_cub3D *game)
{
	if (game->north_compass.img)
		free_img(game->mlx, game->north_compass.img);
	if (game->east_compass.img)
		free_img(game->mlx, game->east_compass.img);
	if (game->south_compass.img)
		free_img(game->mlx, game->south_compass.img);
	if (game->west_compass.img)
		free_img(game->mlx, game->west_compass.img);
}

void	free_minimap_imgs(t_cub3D *game)
{
	if (game->minimap_wall.img)
		free_img(game->mlx, game->minimap_wall.img);
	if (game->minimap_floor.img)
		free_img(game->mlx, game->minimap_floor.img);
	if (game->minimap.img)
		free_img(game->mlx, game->minimap.img);
}

void	free_all_imgs(t_cub3D *game)
{
	free_wall_imgs(game);
	free_compass_imgs(game);
	free_minimap_imgs(game);
	if (game->img.img)
		free_img(game->mlx, game->img.img);
	if (game->sprite)
		free_sprites(game->mlx, game->sprite);
}
