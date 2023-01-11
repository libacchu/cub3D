/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 10:38:48 by libacchu         ###   ########.fr       */
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

void init_game(t_cub3D *game);
int	err_map(int fd, t_cub3D *game);
int count_rows(char *path);
int	create_map_arr(char *str, t_cub3D *game, int fd);
int check_chars(char c);
int check_map(char *str, t_cub3D *game, int fd);
int check_rgb(char *str, t_cub3D *game);
int check_tex(char *str, t_cub3D *game);

int err_message(char *str);
int err_path_name(char *path);
int not_only_white_space(char *str);
int errorcheck(char **argv, t_cub3D *game);



void ft_exit(char *str, t_cub3D *game);



int	ft_key(int keycode,  t_cub3D *game);
int	ft_mouse(t_cub3D *game);

#endif