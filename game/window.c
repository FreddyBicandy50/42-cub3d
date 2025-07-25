/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/26 18:34:16 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


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
	data->north_img = mlx_xpm_file_to_image(data->mlx_ptr, data->north_filename,
			&data->tex_w, &data->tex_h);
	if (!data->north_img)
		exit_and_error(data);
	data->east_img = mlx_xpm_file_to_image(data->mlx_ptr, data->east_filename,
			&data->tex_w, &data->tex_h);
	if (!data->north_img)
		exit_and_error(data);
	data->west_img = mlx_xpm_file_to_image(data->mlx_ptr, data->west_filename,
			&data->tex_w, &data->tex_h);
	if (!data->west_img)
		exit_and_error(data);
	return ;
}

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
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
	mlx_loop(data->mlx_ptr);
}
