/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/14 14:01:16 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include "../minilibx_linux/mlx.h"
# include "../minilibx_linux/mlx_int.h"
# include <math.h>

//# define WINDOW_HEIGHT 480
//# define WINDOW_WIDTH 640
//# define HALF_HEIGHT 240
//# define HALF_WIDTH 320
# define ROTATE_SPEED 0.05
# define MOUSE_SPEED 0.005
# define WALK_SPEED 0.03
# define RUN_SPEED 0.1

# define RESOLUTION 512

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
	KEY_TAB = 65289,
	KEY_SHIFT = 65505,
};

typedef struct s_ray
{
	double	cameraX; // 2 * x / double(w) - 1;
	double	rayDirX; // dirX + planeX * cameraX
	double	rayDirY; // dirY + planeY * cameraX;
	double	sideDistX; // dist to next X block.
	double	sideDistY; // dist to next Y block.
	double	deltaDistX; // dist to X block after next.
	double	deltaDistY; // dist to Y block after next.
	double	perpWallDist;
	int		lineHeight;
	int		drawStart; // height to begin drawing.
	int		drawEnd; // height to finish drawing.
	int		stepX; // direction of the next hit block.
	int		stepY; // direction of the next hit block.
	int		mapX;
	int		mapY;
	int		texX;
	int		texY;
	int		north_x;
	int		north_y;
	int		east_x;
	int		east_y;
	int		south_x;
	int		south_y;
	int		west_x;
	int		west_y;
} t_ray;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
} t_image;

typedef struct s_player
{
	char	direct; // N, S, E, W
	double	posX;	// //x and y start position
	double	posY;
	double	dirX;	//initial direction vector
	double	dirY;
	double	viewX;	//the 2d raycaster version of camera plane
	double	viewY;
}	t_player;

typedef struct s_cub3D
{
	t_player	player;
	t_ray		ray;
	t_image		north_wall;
	t_image		west_wall;
	t_image		east_wall;
	t_image		south_wall;
	t_image		north_compass;
	t_image		east_compass;
	t_image		south_compass;
	t_image		west_compass;

	t_image		minimap_wall;
	t_image		minimap_floor;
	int			map_gen;

	int			ceiling;
	int			floor;
	int			compass;
	int			dark;

	char		*path;
	char		**map_arr;

	int			tab;
	int			shift;
	int			mouse_prev_x;
	int			mouse_prev_y;

	void		*mlx;
	void		*window;
	int			window_height;
	int			window_width;
	int			half_height;
	int			half_width;
	int			x_left_limit;
	int			x_right_limit;
	int			y_up_limit;
	int			y_down_limit;

	t_image		img;

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

int	colourshift(int t, int r, int g, int b);
void make_minimap(t_cub3D *game);

#endif
