/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:11:01 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 13:49:11 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
/* 
	- Keys
		- left/right arrow: allow you to look left and right in the maze.
		- W A S D:  move the point of view through the maze
		- ESC: close the window and quit the program cleanly
		- red cross: close the window and quit the program cleanly.
 */

int	ft_key(int keycode,  t_cub3D *game)
{
	if (keycode == KEY_ESC)
		ft_exit(NULL, game);
	if (keycode == KEY_W || keycode == KEY_UP)
		printf("W\n");
	if (keycode == KEY_A || keycode == KEY_LEFT)
		printf("A\n");
	if (keycode == KEY_S || keycode == KEY_DOWN)
		printf("S\n");
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		printf("D\n");
	return (0);
}

int	ft_mouse(t_cub3D *game)
{
	/* red cross */
	
	ft_exit(NULL, game);
	return (0);
}
