/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 01:01:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;
	double	camera_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		ray.dir_x = data->player.dir_x + data->player.plane_x * camera_x;
		ray.dir_y = data->player.dir_y + data->player.plane_y * camera_x;
		ray.map_x = (int)data->player.x;
		ray.map_y = (int)data->player.y;
		calculate_delta_distance(&ray);
		calculate_step_and_side(&ray, data);
		calculate_dda(data, &ray);
		calculate_wall_height(&ray, data);
		draw_wall_column(data, &ray, x);
		x++;
	}
}

int	render_loop(t_data *data)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = rgb_to_int(data->config.ceiling);
	floor_color = rgb_to_int(data->config.floor);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, floor_color);
			x++;
		}
		y++;
	}
	update_controls(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
