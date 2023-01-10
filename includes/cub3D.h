/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/10 15:49:13 by libacchu         ###   ########.fr       */
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

typedef struct s_player
{
	char	direct;
	int		x;
	int 	y;
} t_player;

typedef struct s_cub3D
{
	t_player	player;
	
	void		*north_wall;
	void		*west_wall;
	void		*east_wall;
	void		*south_wall;
	
	
	int ceiling;
	int floor;
	char *path;
	char **map_arr;


	void *mlx;
} t_cub3D;


#endif