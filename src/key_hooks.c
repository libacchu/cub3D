/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:11:01 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 10:40:12 by libacchu         ###   ########.fr       */
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
	if (keycode == KEY_W)
	
	if (keycode == KEY_A)
	if (keycode == KEY_S)
	if (keycode == KEY_D)

	return (0);
}

int	ft_mouse(t_cub3D *game)
{
	/* red cross */
	
	ft_exit(NULL, game);
	return (0);
}
