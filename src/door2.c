/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:14:01 by obibby            #+#    #+#             */
/*   Updated: 2023/01/18 17:31:54 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_door_node(t_cub3D *game, int new_x, int new_y)
{
	t_door	*door;

	door = game->door_list;
	while (door)
	{
		if (door->x == new_x && door->y == new_y)
			return (door->open);
		door = door->next;
	}
	return (0);
}

void	open_door(t_cub3D *game, int x, int y)
{
	t_door	*door;

	door = game->door_list;
	while (door)
	{
		if (door->x == x && door->y == y)
		{
			if (!door->open)
				door->open = 1;
			else
				door->open = 0;
			break ;
		}
		door = door->next;
	}
}
