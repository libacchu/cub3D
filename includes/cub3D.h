/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/17 13:04:12 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include "../minilibx_linux/mlx.h"
// # include "../minilibx_linux/mlx_int.h"
# include <math.h>
#include <sys/time.h>

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
	KEY_E = 101,
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
	double	*zbuffer;
	int		lineHeight;
	int		drawStart; // height to begin drawing.
	int		drawEnd; // height to finish drawing.
	int		stepX; // direction of the next hit block.
	int		stepY; // direction of the next hit block.
	double	tex_pos;
	double	step;
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

typedef struct s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		err2;
	int		x0;
	int		y0;
	double	x1;
	double	y1;
} t_line;

typedef struct s_door
{
	int		x;
	int		y;
	int		open;
	void	*next;
} t_door;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
} t_image;

typedef	struct s_sprite
{
	int		x;
	int		y;
	int		sp_img;
	int		sp_anime;
	int		sprite_active;
	int		sp_img_total[4];
	void	*next;
} t_sprite;

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

	t_image		minimap;
	t_image		minimap_wall;
	t_image		minimap_floor;
	t_image		minimap_player;
	int			minimap_size_x;
	int			minimap_size_y;
	int			once;

	int			ceiling;
	int			floor;
	int			compass;
	int			ray_colour;

	t_image		door;
	int			doors;
	int			door_hit;
	t_door		*door_list;

	t_sprite	*sprite_list;
	t_sprite	**sprite_arr;
	t_image 	*sprite;
	int			sprite_total;
	

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

	time_t		current_time;
	time_t		last_time;

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
void	set_screen_size(t_cub3D *game);
int		assign_images(t_cub3D *game);

int		check_x(int c);
int		check_y(char **map_arr, int y, int x);
int		check_walls_chars(t_cub3D *game, int x, int y);
int		loop_x(t_cub3D *game, int x, int y);

int		err_message(char *str);
int		err_path_name(char *path);
int		only_white_space(char *str);
int		errorcheck(char **argv, t_cub3D *game);

double	ft_abs(double x);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	ft_swap(int *distance_x, int *distance_y, int *order_x, int *order_y);

void	ft_exit(char *str, t_cub3D *game);
void	ft_free(t_cub3D *game);

int		ft_key(int keycode, t_cub3D *game);
int		ft_mouse(t_cub3D *game);

void	move_player(t_cub3D *game, double y, double x, int grad);
void	rotate_player(t_cub3D *game, int dir);

int	add_door(t_cub3D *game, int x, int y);
int	check_door(t_cub3D *game, int side);
void	assign_door(t_cub3D *game);
void	get_door_colour(t_cub3D *game, t_image *img, int x, int y);
void	find_door(t_cub3D *game);
void	open_door(t_cub3D *game, int x, int y);

int		colourshift(int t, int r, int g, int b);
int		raycast(t_cub3D *game);
void	make_minimap(t_cub3D *game);
void	refresh_minimap(t_cub3D *game);
void	get_pixel_colour(t_cub3D *game, t_image *img, int x, int y);
void	line_algo(t_cub3D *game, int x, int y);

void	init_ray(t_cub3D *game, int x);
void	init_compass(t_cub3D *game);
void	put_compass(t_cub3D *game, int x, int y);
void	get_delta_dist(t_cub3D *game);
void	get_side_dist(t_cub3D *game);
void	get_perp_wall_dist(t_cub3D *game, int side);
void	get_hit(t_cub3D *game, int *side);
void	get_draw_coords(t_cub3D *game);
void	get_tex_pos(t_cub3D *game, int side);

t_image	*set_image_ptr(t_cub3D *game, int side);
void	draw_to_image(t_cub3D *game, int x, t_image *img);
void	put_images_to_window(t_cub3D *game);
void	pixel_put_image(t_cub3D *game, t_image *img, int x, int y);

void	player_start_direction(int x, int y, t_cub3D *game);
int		mouse_move(int x, int y, t_cub3D *game);

int	check_sprite(t_cub3D *game, int side);
void	assign_sprite(t_cub3D *game);

void	get_pixel_colour(t_cub3D *game, t_image *img, int x, int y);
void	get_sprite_colour(t_cub3D *game, int x, int y);
int	check_colour_pix(t_image *data, int x, int y);

int	add_sprite(t_cub3D *game, int x, int y);

time_t	get_time_in_ms(void);

#endif
