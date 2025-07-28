/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:57:51 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/28 18:51:34 by fbicandy         ###   ########.fr       */
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

# define MOVMENT_SPEED 0.03
# define BUFFER_SIZE 1024
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
# define ROT_SPEED 0.025

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_matrix
{
	int			width;
	int			height;
	int			**matrix;
}				t_matrix;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;

	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			color;

	double		player_x;
	double		player_y;
	double		player_dir;
	t_player	player;

	char		*north_filename;
	char		*south_filename;
	char		*west_filename;
	char		*east_filename;
	char		*floor_color;
	char		*ceiling_color;

	void		*north_img;
	void		*south_img;
	void		*east_img;
	void		*west_img;

	int			fd;
	char		**map;
	ssize_t		bytes_read;
	char		*file_buffer;
	char		*map_filename;
	char		**map_content;
	char		*error_message;

	int			tex_w;
	int			tex_h;

	int			has_no;
	int			has_so;
	int			has_we;
	int			has_ea;
	int			has_floor;
	int			has_ceiling;
	int			position;
	int			x_coordinate;
	int			y_coordinate;
	int			set;
}				t_data;

// render.c
int				rendering(t_data *data);

// window
void			init_textures(t_data *data);
void			create_window(t_data *data);

// libft
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*word_dup(const char *str, int start, int finish);
int				count_words(const char *str, char c);
char			*ft_strchr(const char *s, int c);
void			ft_strcpy(char *dest, char *src);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcmp(char *s1, char *s2);
void			ft_bzero(void *s, size_t n);
char			*ft_strrchr(char *s, int c);
char			**ft_split(char *s, char c);
int				ft_atoi(const char *nptr);
char			*ft_strdup(char *str);
int				ft_strlen(char *str);
int				ft_isdigit(int c);

// parsing
int				is_map(char *line);
int				open_map(t_data *p);
int				read_map(t_data *p);
void			parse_map(t_data *p);
int				check_mapcontent(t_data *p);
int				extract_mapcontent(t_data *p);
int				parse_line(t_data *p, char *line);
int				parse_line_utils(t_data *p, char *line);

// map parsing
int				validate_map(t_data *p);
int				check_previous_line(t_data *p, char *line, char *previous_line);
int				check_next_line(t_data *p, char *line, char *next_line);
int				check_column_map(char *line, t_data *p);
int				check_row_map(char *line, t_data *p);
int				process_map(char *line, t_data *p, int *len);
int				check_char_map(t_data *p, char *line, int *i);
int				is_correct_coordinate(t_data *p);
int				recheck_mapwalls(t_data *p, char *line, int *len);

// parsing utils
int				check_texture(char *filename);
void			copy_map(t_data *p, int map_start);
void			trimwhitespace_str(char *line);
void			set_x_coordinate(t_data *p, int i);

// color_parsing
int				check_color(char *color, t_data *p);
int				recheck_colors(char **colors);
int				handle_color(char **colors, t_data *p);
int				check_char_color(char **colors);
int				parse_line_colors(t_data *p, char *line);
int				is_valid_color_format(char *line);
// directions
int				north(t_data *p, char *line);
int				south(t_data *p, char *line);
int				west(t_data *p, char *line);
int				east(t_data *p, char *line);
int				floorcolor(t_data *p, char *line);
int				ceiling(t_data *p, char *line);

// utils
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			init_player(t_data **p);
void			initialize_struct(t_data *p);
void			error_message(char *str);
void			free_2d_array(char **array);
void			free_allocated(t_data *p);
void			exit_and_error(t_data *p);
void			initialize_struct(t_data *p);
char			**malloc_2d_copy(char **src);
int				copy_map_lines(t_data *p, int map_start, int finish);

// floodfill
int				is_out_of_bounds(char **map, int x, int y);
int				is_invalid_tile(char tile);
void			fill(char **map, int x, int y, int *error);
int				flood_fill_check(t_data *p);
char			**malloc_2d_copy(char **original);
#endif
