/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/11 14:41:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include "../minilibx_linux/mlx.h"

// Keyboard
enum	e_keystroke
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_UP = 65362,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
};

typedef struct s_player
{
	char	direct;
	int		x;
	int		y;
}	t_player;

typedef struct s_cub3D
{
	t_player	player;
	void		*north_wall;
	void		*west_wall;
	void		*east_wall;
	void		*south_wall;

	void	*minimap_wall;
	void	*minimap_floor;

	int			ceiling;
	int			floor;
	char		*path;
	char		**map_arr;

	void		*mlx;
	void		*window;
}	t_cub3D;

void	init_game(t_cub3D *game);
int		err_map(int fd, t_cub3D *game);
int		count_rows(char *path);
int		create_map_arr(char *str, t_cub3D *game, int fd);
int		check_chars(char c);
int		check_map(char *str, t_cub3D *game, int fd);
int		check_rgb(char *str, t_cub3D *game);
int		check_tex(char *str, t_cub3D *game);

int		check_x(int c);
int		check_y(char **map_arr, int y, int x);
int		check_walls_chars(t_cub3D *game, int x, int y);
int		loop_x(t_cub3D *game, int x, int y);

int		err_message(char *str);
int		err_path_name(char *path);
int		only_white_space(char *str);
int		errorcheck(char **argv, t_cub3D *game);

void	ft_exit(char *str, t_cub3D *game);

int		ft_key(int keycode, t_cub3D *game);
int		ft_mouse(t_cub3D *game);

#endif
