/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/09 13:08:45 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>

// Keyboard
enum	e_keystroke
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
};

typedef struct s_cub3D
{
	void *north_wall;
	void *west_wall;
	void *east_wall;
	void *south_wall;
	int ceiling;
	int floor;
} t_cub3D;

#endif