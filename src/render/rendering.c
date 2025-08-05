/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 23:23:29 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	draw_wall_column(t_data *data, t_ray *ray, int x)
// {
// 	int			y;
// 	double		step;
// 	double		pos;
// 	int			tex_y;
// 	int			color;
// 	int			tex_index;
// 	t_texture	*tex;
// 	int			*texture;

// 	if (ray->side == 0)
// 	{
// 		if (ray->dir_x < 0)
// 			tex_index = 0;
// 		else
// 			tex_index = 1;
// 	}
// 	else
// 	{
// 		if (ray->dir_y < 0)
// 			tex_index = 2;
// 		else
// 			tex_index = 3;
// 	}
// 	tex = &data->config.textures[tex_index];
// 	if (!tex || !tex->img_data)
// 	{
// 		ft_putstr_fd("Error\nMissing texture data\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	texture = (int *)tex->img_data;
// 	ray->tex_x = (int)(ray->wall_x * tex->width);
// 	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
// 			&& ray->dir_y > 0))
// 		ray->tex_x = tex->width - ray->tex_x - 1;
// 	step = (double)tex->height / ray->line_height;
// 	pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		tex_y = (int)pos;
// 		pos += step;
// 		color = texture[tex->width * tex_y + ray->tex_x];
// 		printf("hello5");
// 		exit(0);
// 		my_mlx_pixel_put(data, x, y, color);
// 		y++;
// 	}
// }

void	draw_wall_column(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = 0x00FF00; // green test wall
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	calculate_wall_height(t_ray *r, t_data *d)
{
	if (r->side == 0)
		r->wall_dist = (r->map_x - d->player.x + (1 - r->step_x) / 2.0)
			/ r->dir_x;
	else
		r->wall_dist = (r->map_y - d->player.y + (1 - r->step_y) / 2.0)
			/ r->dir_y;
	r->line_height = (int)(WIN_HEIGHT / r->wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = d->player.y + r->wall_dist * r->dir_y;
	else
		r->wall_x = d->player.x + r->wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
}

void	calculate_dda(t_data *data, t_ray *r)
{
	while (1)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (data->map.grid[r->map_y][r->map_x] == '1')
			break ;
	}
}

void	calculate_step_and_side(t_ray *r, t_data *d)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (d->player.x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - d->player.x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (d->player.y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - d->player.y) * r->delta_y;
	}
}

void	calculate_delta_distance(t_ray *r)
{
	if (r->dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1 / r->dir_y);
}

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

int	render_loop(void *param)
{
	t_data	*data;
	int		x;
	int		y;
	int		ceiling_color;
	int		floor_color;

	data = (t_data *)param;
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
	raycast(data);
	printf("DEBUG: After parsing, before finding player:\n");
	printf("Player at: x=%.2f y=%.2f\n", data->player.x, data->player.y);
	printf("Direction : x=%.2f y=%.2f\n", data->player.dir_x,
		data->player.dir_y);
	printf("Plane     : x=%.2f y=%.2f\n", data->player.plane_x,
		data->player.plane_y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
