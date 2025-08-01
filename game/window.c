/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/01 22:20:46 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_start(t_data *p)
{
	char	dir;

	if (p->x_coordinate < 0 || p->y_coordinate < 0)
	{
		p->error_message = "Player start position not found";
		exit_and_error(p);
	}
	p->player.pos_x = p->y_coordinate + 0.5;
	p->player.pos_y = p->x_coordinate + 0.5;
	dir = p->map[p->x_coordinate][p->y_coordinate];
	if (dir == 'N')
	{
		p->player.dir_x = 0;
		p->player.dir_y = -1;
		p->player.plane_x = 0.66;
		p->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->player.dir_x = 0;
		p->player.dir_y = 1;
		p->player.plane_x = -0.66;
		p->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		p->player.dir_x = 1;
		p->player.dir_y = 0;
		p->player.plane_x = 0;
		p->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->player.dir_x = -1;
		p->player.dir_y = 0;
		p->player.plane_x = 0;
		p->player.plane_y = -0.66;
	}
	p->map[p->x_coordinate][p->y_coordinate] = '0';
}

void	init_textures(t_data *data)
{
	data->north_img = mlx_xpm_file_to_image(data->mlx_ptr, data->north_filename,
			&data->tex_w, &data->tex_h);
	if (!data->north_img)
		exit_and_error(data);
	data->south_img = mlx_xpm_file_to_image(data->mlx_ptr, data->south_filename,
			&data->tex_w, &data->tex_h);
	if (!data->south_img)
		exit_and_error(data);
	data->east_img = mlx_xpm_file_to_image(data->mlx_ptr, data->east_filename,
			&data->tex_w, &data->tex_h);
	if (!data->east_img)
		exit_and_error(data);
	data->west_img = mlx_xpm_file_to_image(data->mlx_ptr, data->west_filename,
			&data->tex_w, &data->tex_h);
	if (!data->west_img)
		exit_and_error(data);
	data->north_img = mlx_xpm_file_to_image(data->mlx_ptr, data->north_filename,
			&data->tex_w, &data->tex_h);
	data->north_buf = (int *)mlx_get_data_addr(data->north_img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return ;
}

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->mlx_ptr)
	{
		error_message("Error initializing mlx\n");
		exit(EXIT_FAILURE);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!data->win_ptr)
	{
		error_message("Error creating window\n");
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(EXIT_FAILURE);
	}
}
