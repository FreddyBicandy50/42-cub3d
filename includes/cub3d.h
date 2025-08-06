/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:33:28 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 14:28:10 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include "libft.h"
# include <../minilibx-linux/mlx.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef DEFINES_H
#  define DEFINES_H

#  define WIN_WIDTH 1920
#  define WIN_HEIGHT 1080
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define BUFFER_SIZE 42
#  define COLOR_FLOOR 0x222222
#  define COLOR_CEILING 0x888888

#  define MOVE_SPEED 0.01
#  define ROT_SPEED 0.03
# endif

typedef struct s_input
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_input;

// ----------------------
// RGB Color
// ----------------------
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
// ----------------------
// Texture Info (XPM images)
// ----------------------
typedef struct s_texture
{
	void		*img_ptr;

	int			bpp;
	int			width;
	int			height;
	int			endian;
	int			line_len;

	char		*img_data;
}				t_texture;
// ----------------------
// Configuration Info from .cub
// ----------------------
typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	t_texture	textures[4];

	t_color		floor;
	t_color		ceiling;
}				t_config;
// ----------------------
// Map Data
// ----------------------
typedef struct s_map
{
	int			width;
	int			height;

	char		**grid;
}				t_map;
// ----------------------
// Player Info
// ----------------------
typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;
// ----------------------
// Raycasting & Game State
// ----------------------
typedef struct s_ray
{
	int			color;
	int			tex_x;
	int			tex_y;
	int			side;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			draw_end;
	int			tex_index;
	int			draw_start;
	int			line_height;

	double		dir_x;
	double		dir_y;
	double		wall_x;
	double		delta_x;
	double		delta_y;
	double		wall_dist;
	double		side_dist_y;
	double		side_dist_x;
}				t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	int			fd;
	int			bpp;
	int			endian;
	int			line_len;

	char		*img_data;

	t_map		map;
	t_input		input;
	t_config	config;
	t_player	player;
}				t_data;

char			*get_next_line(int fd);

// handle_keys.c
void			move_left(t_data *data);
void			move_right(t_data *data);
void			move_backward(t_data *data);
void			move_forward(t_data *data);
// handle_rotations.c
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);

// free_game.c
void			free_game(t_data *game);
void			free_given_file(t_data *game);

// parse_file.c
void			parse_cub_file(t_data *game, int fd);
// parse_file1.c
int				is_direction(char *line);
int				is_ceil_floor(char *line);
int				valid_file_extension(char *filename, char *ext);
void			parse_direction(t_data *game, char **splitted);
void			parse_single_direction(char **dest_path, char **splitted,
					t_data *game);
// parse_file2.c
int				count_commas(char *line);
int				check_color_range(t_color color);
void			check_digit(t_data *game, char **split_rgb, char **splitted);
void			parse_ceiling(t_data *game, char **splitted, char **split_rgb);
void			parse_single_color(t_data *game, char **splitted,
					char **split_rgb);

// parse_file3.c
char			*replace_tabs_with_spaces(char *line);
void			parse_config(t_data *game, char *line);
void			parse_rgb(t_data *game, char **splitted);

// parse_file4.c
int				is_map(char *line);

int				is_empty_line(char *line);
int				error_exit(t_data *game, char *str, char *error_message);
int				error_exit_matrix(t_data *game, char **matrix,
					char *error_message);
int				error_exit_matrix_rgb(t_data *game, char **color, char **matrix,
					char *error_message);

// utils.c

void			free_matrix(char **matrix);
void			init_data(t_data *game);

// validate_map.c
int				is_player_char(char c);
int				is_fillable(char c);
char			**copy_map(char **src, int height);
int				flood_fill(char **map, int x, int y, t_data *game);

// validate_map1.c
int				validate_map_walls(t_data *game);
void			normalize_map_width(t_data *game);
char			*pad_line(const char *line, int target_width);

// validate_map2.c
int				validate_map(t_data *game);
void			parse_map(t_data *game, char *line);

// handle_keys
void			update_controls(t_data *data);
int				handle_key(int keycode, t_data *data);
int				handle_key_release(int keycode, t_data *data);
// player
void			find_player_start(t_data *data);
void			set_player_start(t_data *data, int i, int j);

// windows.c
int				close_window(t_data *data);
void			create_window(t_data *data);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

// calculations.c
void			calculate_wall_height(t_ray *r, t_data *d);
void			calculate_dda(t_data *data, t_ray *r);
void			calculate_delta_distance(t_ray *r);
void			calculate_step_and_side(t_ray *r, t_data *d);

// rendering
int				render_loop(t_data *param);

// handle_keys.c
void			update_controls(t_data *data);
int				handle_key(int keycode, t_data *data);
int				handle_key_release(int keycode, t_data *data);

// textures.c
void			draw_wall_column(t_data *data, t_ray *ray, int x);
#endif