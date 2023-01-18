/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:42:39 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 16:10:26 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	add_sprite(t_cub3D *game, int x, int y)
{
	t_sprite	*new_sprite;
	t_sprite	*sprite;

	new_sprite = ft_calloc(1, sizeof(t_sprite));
	if (!new_sprite)
		return (err_message("Failed to allocate memory.\n"));
	new_sprite->x = x + 0.5;
	new_sprite->y = y + 0.5;
	new_sprite->sp_img = 5;
	new_sprite->sp_anime = 0;
	new_sprite->sprite_active = 1;
	new_sprite->next = NULL;
	if (!game->sprite_list)
		game->sprite_list = new_sprite;
	else
	{
		sprite = game->sprite_list;
		while (sprite->next)
			sprite = sprite->next;
		sprite->next = new_sprite;
	}
	game->sprite_total++;
	return (0);
}

void	add_data_addr(t_image *img)
{
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->line_size, &img->endian);
}

int	assign_sprite(t_cub3D *game)
{
	int	x;
	int	y;

	game->sprite = ft_calloc(4, sizeof(t_image));
	game->sprite[0].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-appears.xpm", &x, &y);
	game->sprite[1].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-idle.xpm", &x, &y);
	game->sprite[2].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-shriek.xpm", &x, &y);
	game->sprite[3].img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprites/ghost-vanish.xpm", &x, &y);
	if (!game->sprite[0].img || !game->sprite[1].img \
		|| !game->sprite[2].img || !game->sprite[3].img)
		return (err_message("Sprite image not loaded!"));
	add_data_addr(&game->sprite[0]);
	add_data_addr(&game->sprite[1]);
	add_data_addr(&game->sprite[2]);
	add_data_addr(&game->sprite[3]);
	game->ray.zbuffer = ft_calloc(game->window_width, sizeof(double));
	return (0);
}

int	init_sprite_node(t_sprite **sprite, t_sprite	*node)
{
	*sprite = ft_calloc(1, sizeof(t_sprite));
	(*sprite)->x = node->x;
	(*sprite)->y = node->y;
	(*sprite)->sp_anime = 0;
	(*sprite)->sp_img = 0;
	(*sprite)->sp_img_total[0] = 6;
	(*sprite)->sp_img_total[1] = 7;
	(*sprite)->sp_img_total[2] = 4;
	(*sprite)->sp_img_total[3] = 7;
	(*sprite)->sprite_active = 0;
	(*sprite)->sprite_deactivate = 0;
	return (0);
}

int	make_sprite_array(t_cub3D *game)
{
	t_sprite	*node;
	t_sprite	*prev;
	int			i;

	node = game->sprite_list;
	game->sprite_arr = ft_calloc(game->sprite_total + 1, sizeof(t_sprite *));
	if (!game->sprite_arr)
		return (err_message("Memory allocation failed."));
	i = 0;
	while (node)
	{
		init_sprite_node(&game->sprite_arr[i], node);
		prev = node;
		node = node->next;
		free(prev);
		i++;
	}
	return (0);
}
