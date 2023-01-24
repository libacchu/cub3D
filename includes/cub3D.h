/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:15:28 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/24 11:42:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../minilibx_linux/mlx.h"

# define ROTATE_SPEED 0.05
# define MOUSE_SPEED 0.005
# define WALK_SPEED 0.03
# define RUN_SPEED 0.1

# define RESOLUTION 512

# ifdef __MACH__
#  define SYSTEM 1
# elif __linux__
#  define SYSTEM 2
# endif

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
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	*zbuffer;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		step_x;
	int		step_y;
	double	tex_pos;
	double	step;
	int		map_x;
	int		map_y;
	int		tex_x;
	int		tex_y;
	int		north_x;
	int		north_y;
	int		east_x;
	int		east_y;
	int		south_x;
	int		south_y;
	int		west_x;
	int		west_y;
}	t_ray;

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
}	t_line;

typedef struct s_door
{
	int		x;
	int		y;
	int		open;
	void	*next;
}	t_door;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		sp_img;
	int		sp_anime;
	int		sprite_active;
	int		sprite_activate;
	int		sprite_deactivate;
	int		sprite_scare;
	int		sp_img_total[4];
	void	*next;
}	t_sprite;

typedef struct s_spr_cast
{
	double	trans_y;
	int		s_screen_x;
	int		s_height;
	int		draw_start_y;
	int		draw_end_y;
	int		s_width;
	int		draw_start_x;
	int		draw_end_x;
	int		index;
}	t_spr_cast;

typedef struct s_player
{
	char	direct;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	view_x;
	double	view_y;
}	t_player;

typedef struct s_cub3D
{
	t_player	player;
	t_ray		ray;
	t_image		north_wall;
	t_image		west_wall;
	t_image		east_wall;
	t_image		south_wall;
	char		*north_wall_addr;
	char		*east_wall_addr;
	char		*south_wall_addr;
	char		*west_wall_addr;
	t_image		north_compass;
	t_image		east_compass;
	t_image		south_compass;
	t_image		west_compass;

	int			up_key;
	int			down_key;
	int			left_key;
	int			right_key;

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
	t_spr_cast	sprite_info;
	t_image		*sprite;
	int			sprite_total;
	int			*sprite_order;
	int			*sprite_distance;
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

int		free_strings(t_cub3D *game);

/* assign_images */
int		assign_compass(t_cub3D *game);
int		assign_minimap(t_cub3D *game);
int		assign_walls_ns(t_cub3D *game);
int		assign_walls_ew(t_cub3D *game);
int		assign_images(t_cub3D *game);

/* door.c */
int		add_door(t_cub3D *game, int x, int y);
int		assign_door(t_cub3D *game);
int		check_door(t_cub3D *game, int side);
void	get_door_colour(t_cub3D *game, t_image *img, int x, int y);
void	find_door(t_cub3D *game);

/* door2.c */
int		find_door_node(t_cub3D *game, int new_x, int new_y);
void	open_door(t_cub3D *game, int x, int y);

/* game_init.c */
void	set_screen_size(t_cub3D *game);

/* err_file_check.c */
int		map_checks(t_cub3D *game, char **str, int fd, int i);
int		premap_check(t_cub3D *game, char *str);
int		err_map(int fd, t_cub3D *game);

/* err_map_check.c */
int		check_x(int c);
int		check_y(char **map_arr, int y, int x);
int		check_walls_chars(t_cub3D *game, int x, int y);
int		loop_x(t_cub3D *game, int x, int y);
int		check_map(char **str, t_cub3D *game, int fd);

/* err_map_check2.c */
int		count_rows(char *path);
int		add_to_arr(char **str, t_cub3D *game, int fd);
int		create_map_arr(char **str, t_cub3D *game, int fd);
int		check_chars(char c);

/* err_rgb_check.c */
int		colourshift(int t, int r, int g, int b);
int		convert_number(char *str, int *i, int *n);
int		set_rgb(char *str, int *colour);
int		check_rgb(char *str, t_cub3D *game);

/* err_tex_check.c */
int		alloc_wall(char *str, char **wall_ptr);
int		check_tex(char *str, t_cub3D *game);

/* error_check.c */
int		err_message(char *str);
int		err_path_name(char *path);
int		only_white_space(char *str);
int		errorcheck(char **argv, t_cub3D *game);

/* exit.c */
void	ft_exit(char *str, t_cub3D *game);

/* free_game_imgs.c */
void	free_wall_imgs(t_cub3D *game);
void	free_compass_imgs(t_cub3D *game);
void	free_minimap_imgs(t_cub3D *game);
void	free_sprite_arr(t_cub3D *game);
void	free_all_imgs(t_cub3D *game);

/* free.c */
void	free_array(char **str);
void	free_img(void *mlx, void *ptr);
void	free_sprites(void *mlx, t_image *sprite);
int		ft_free(t_cub3D *game);

/* game_init.c */
void	init_game(t_cub3D *game);
void	set_screen_size(t_cub3D *game);

/* image.c */
void	put_images_to_window(t_cub3D *game);
void	get_pixel_colour(t_cub3D *game, t_image *img, int x, int y);
void	draw_to_image(t_cub3D *game, int x, t_image *img);
t_image	*set_image_ptr(t_cub3D *game, int side);
void	pixel_put_image(t_cub3D *game, t_image *img, int x, int y);

/* key_hook.c */
void	toggle_shift(t_cub3D *game);
void	toggle_tab(t_cub3D *game);
int		ft_key_press(int keycode, t_cub3D *game);
int		ft_key_release(int keycode, t_cub3D *game);
int		ft_mouse(t_cub3D *game);

/* lines.c */
void	draw_line(t_cub3D *game, t_line *line);
void	line_algo(t_cub3D *game, int x, int y);

/* minimap.c */
void	make_minimap(t_cub3D *game);
void	refresh_minimap(t_cub3D *game);

/* mouse_move.c */
void	rotate_left(t_cub3D *game, int x_dif);
void	rotate_right(t_cub3D *game, int x_dif);
int		mouse_move(int x, int y, t_cub3D *game);

/* movement.c */
void	rotate_player(t_cub3D *game, int dir);
void	move_player(t_cub3D *game, double y, double x, int grad);

/* player_direction.c */
void	player_start_direction(int x, int y, t_cub3D *game);

/* put_sprite.c */
void	put_sprite_colour(t_cub3D *game, int tex_x, int x, int y);
void	put_sprite(t_cub3D *game, t_spr_cast *info);
int		draw_sprites(t_cub3D *game);

/* raycast_calc_2.c */
void	get_draw_coords(t_cub3D *game);
void	get_tex_pos(t_cub3D *game, int side);
void	put_compass(t_cub3D *game, int x, int y);
void	init_compass(t_cub3D *game);

/* raycast_calc.c */
void	init_ray(t_cub3D *game, int x);
void	get_delta_dist(t_cub3D *game);
int		get_hit(t_cub3D *game);
void	get_side_dist(t_cub3D *game);
void	get_perp_wall_dist(t_cub3D *game, int side);

/* raycast.c */
void	make_minimap(t_cub3D *game);
void	raycast(t_cub3D *game);
int		render(t_cub3D *game);

/* sprite_anim.c */
void	scare_sprite(t_cub3D *game, int i);
void	deactivate_scare(t_cub3D *game, int i);
void	deactivate_sprite(t_cub3D *game, int i);
void	activate_sprite(t_cub3D *game, int i);
void	idle_sprite(t_cub3D *game, int i);

/* sprite_cast.c */
void	sort_sprites(int *sprite_order, \
		int *sprite_distance, int total_sprites);
int		get_sprite_dist(t_cub3D *game);
void	get_sprite_coords(t_cub3D *game, t_spr_cast *info);
void	get_sprite_size(t_cub3D *game, t_spr_cast *info, int i);

/* sprite_move.c */

void	move_sprite(t_cub3D *game, int i);
void	inc_anims(t_cub3D *game);

/* sprite.c */
int		add_sprite(t_cub3D *game, int x, int y);
void	add_data_addr(t_image *img);
int		assign_sprite(t_cub3D *game);
int		make_sprite_array(t_cub3D *game);

/* utils.c */
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	ft_swap(int *distance_x, int *distance_y, int *order_x, int *order_y);
double	ft_abs(double x);
void	play_sound(char *str);
time_t	get_time_in_ms(void);

#endif
