/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:57:51 by adahroug          #+#    #+#             */
/*   Updated: 2025/08/01 22:58:21 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include <../.minilibx-linux/mlx.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TEXTURE_SIZE 64
# define MOVMENT_SPEED 0.03
# define BUFFER_SIZE 1024
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define ROT_SPEED 0.025

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}						t_cardinal_direction;

typedef struct s_raycasting
{
	int					side;
	int					map_x;
	int					map_y;
	int					tex_x;
	int					step_x;
	int					step_y;
	int					draw_end;
	int					draw_start;
	int					line_height;
	double				wall_x;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				wall_dist;
}						t_raycasting;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_player;

typedef struct s_matrix
{
	int					width;
	int					height;
	int					**matrix;
}						t_matrix;

typedef struct s_data
{
	int					floor_rgb;
	int					ceiling_rgb;

	int					*east_buf;
	int					*west_buf;
	int					*north_buf;
	int					*south_buf;

	char				*addr;
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;

	int					color;
	int					endian;
	t_player			player;
	int					line_length;
	char				*player_dir;
	int					bits_per_pixel;

	char				*floor_color;
	char				*east_filename;
	char				*west_filename;
	char				*ceiling_color;
	char				*north_filename;
	char				*south_filename;

	void				*east_img;
	void				*west_img;
	void				*north_img;
	void				*south_img;

	int					fd;
	char				**map;
	ssize_t				bytes_read;
	char				*file_buffer;
	char				*map_filename;
	char				**map_content;
	char				*error_message;

	int					tex_w;
	int					tex_h;

	int					set;
	int					has_no;
	int					has_so;
	int					has_we;
	int					has_ea;
	int					position;
	int					has_floor;
	int					has_ceiling;
	int					x_coordinate;
	int					y_coordinate;
}						t_data;

// render.c
int						raycast(t_data *p);
int						render_loop(void *param);

// window
void					set_player_start(t_data *p);
void					init_textures(t_data *data);
void					create_window(t_data *data);

// libft
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_substr(char *s, unsigned int start, size_t len);
char					*word_dup(const char *str, int start, int finish);
int						count_words(const char *str, char c);
char					*ft_strchr(const char *s, int c);
void					ft_strcpy(char *dest, char *src);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strcmp(char *s1, char *s2);
void					ft_bzero(void *s, size_t n);
char					*ft_strrchr(char *s, int c);
char					**ft_split(char *s, char c);
int						ft_atoi(const char *nptr);
char					*ft_strdup(char *str);
int						ft_strlen(char *str);
int						ft_isdigit(int c);

// parsing
int						is_map(char *line);
int						open_map(t_data *p);
int						read_map(t_data *p);
void					parse_map(t_data *p);
int						check_mapcontent(t_data *p);
int						extract_mapcontent(t_data *p);
int						parse_line(t_data *p, char *line);
int						parse_line_utils(t_data *p, char *line);

// map parsing
int						validate_map(t_data *p);
int						check_previous_line(t_data *p, char *line,
							char *previous_line);
int						check_next_line(t_data *p, char *line, char *next_line);
int						check_column_map(char *line, t_data *p);
int						check_row_map(char *line, t_data *p);
int						process_map(char *line, t_data *p, int *len);
int						check_char_map(t_data *p, char *line, int *i);
int						is_correct_coordinate(t_data *p);
int						recheck_mapwalls(t_data *p, char *line, int *len);

// parsing utils
int						check_texture(char *filename);
void					copy_map(t_data *p, int map_start);
void					trimwhitespace_str(char *line);
void					set_x_coordinate(t_data *p, int i);

// color_parsing
int						rgb_to_int(char *rgb_string);
int						check_color(char *color, t_data *p);
int						recheck_colors(char **colors);
int						handle_color(char **colors, t_data *p);
int						check_char_color(char **colors);
int						parse_line_colors(t_data *p, char *line);
int						is_valid_color_format(char *line);
// directions
int						north(t_data *p, char *line);
int						south(t_data *p, char *line);
int						west(t_data *p, char *line);
int						east(t_data *p, char *line);
int						floorcolor(t_data *p, char *line);
int						ceiling(t_data *p, char *line);

// utils
void					init_player(t_data **p);
void					initialize_struct(t_data *p);
void					error_message(char *str);
void					free_2d_array(char **array);
void					free_allocated(t_data *p);
void					exit_and_error(t_data *p);
void					initialize_struct(t_data *p);
char					**malloc_2d_copy(char **src);
t_cardinal_direction	ft_get_cardinal_direction(t_raycasting *ray);
int						copy_map_lines(t_data *p, int map_start, int finish);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);

// floodfill
int						is_out_of_bounds(char **map, int x, int y);
int						is_invalid_tile(char tile);
void					fill(char **map, int x, int y, int *error);
int						flood_fill_check(t_data *p);
char					**malloc_2d_copy(char **original);
#endif
