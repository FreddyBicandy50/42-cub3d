/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:04 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/01 23:07:19 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall_column(t_data *data, t_raycasting *ray, int x)
{
	int						y;
	double					pos;
	double					step;
	int						tex_y;
	int						color;
	int						*tex;
	t_cardinal_direction	dir;

	dir = ft_get_cardinal_direction(ray);
	ray->tex_x = (int)(ray->wall_x * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		ray->tex_x = TEXTURE_SIZE - ray->tex_x - 1;
	step = 1.0 * TEXTURE_SIZE / ray->line_height;
	pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	if (dir == NORTH)
		tex = data->north_buf;
	else if (dir == SOUTH)
		tex = data->south_buf;
	else if (dir == WEST)
		tex = data->west_buf;
	else
		tex = data->east_buf;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += step;
		color = tex[TEXTURE_SIZE * tex_y + ray->tex_x];
		if (dir == NORTH || dir == SOUTH)
			color = (color >> 1) & 0x7F7F7F;
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

/*
	The final step in the raycasting algorithm is to calculate the height of
	the wall based on the distance to the wall and the player’s view.
*/
void	calculate_wall_height(t_raycasting *raycast, t_data *data)
{
	if ((*raycast).side == 0)
		(*raycast).wall_dist = (raycast->map_x - data->player.pos_x + (1
					- raycast->step_x) / 2.0) / raycast->ray_dir_x;
	else
		(*raycast).wall_dist = ((*raycast).map_y - data->player.pos_y + (1
					- (*raycast).step_y) / 2.0) / raycast->ray_dir_y;
	(*raycast).line_height = (int)(WIN_HEIGHT / (*raycast).wall_dist);
	(*raycast).draw_start = -(*raycast).line_height / 2 + WIN_HEIGHT / 2;
	if ((*raycast).draw_start < 0)
		(*raycast).draw_start = 0;
	(*raycast).draw_end = (*raycast).line_height / 2 + WIN_HEIGHT / 2;
	if ((*raycast).draw_end >= WIN_HEIGHT)
		(*raycast).draw_end = WIN_HEIGHT - 1;
	if ((*raycast).side == 0)
		(*raycast).wall_x = data->player.pos_y + (*raycast).wall_dist
			* (*raycast).ray_dir_y;
	else
		(*raycast).wall_x = data->player.pos_x + (*raycast).wall_dist
			* (*raycast).ray_dir_x;
	(*raycast).wall_x -= floor((*raycast).wall_x);
}

/*

	The next step in the raycasting algorithm is to perform Digital Differential Analysis (DDA)
	to determine the distance to the next grid line in the x or y direction.
	This involves stepping through the grid and calculating the distance to the next grid line in each direction.
	We also take note of the side of the wall we hit (0 for x,1 for y).
*/
void	calculate_dda(t_data *data, t_raycasting *raycast)
{
	while (42)
	{
		if ((*raycast).side_dist_x < (*raycast).side_dist_y)
		{
			(*raycast).side_dist_x += (*raycast).delta_dist_x;
			(*raycast).map_x += (*raycast).step_x;
			(*raycast).side = 0;
		}
		else
		{
			(*raycast).side_dist_y += (*raycast).delta_dist_y;
			(*raycast).map_y += (*raycast).step_y;
			(*raycast).side = 1;
		}
		if (data->map[(*raycast).map_y][(*raycast).map_x] == '1')
			break ;
	}
}

/*
	The side_dist_x and side_dist_y variables represent initially the distance the ray must travel from its
	current position to the next grid line in the x or y direction.
	Later these variables will be updated with the delta distance as the ray moves through the grid.
*/
void	calculate_step_and_side(t_raycasting *raycast, t_data *p)
{
	if ((*raycast).ray_dir_x < 0)
	{
		(*raycast).step_x = -1;
		(*raycast).side_dist_x = (p->player.pos_x - (*raycast).map_x)
			* (*raycast).delta_dist_x;
	}
	else
	{
		(*raycast).step_x = 1;
		(*raycast).side_dist_x = ((*raycast).map_x + 1.0 - p->player.pos_x)
			* (*raycast).delta_dist_x;
	}
	if ((*raycast).ray_dir_y < 0)
	{
		(*raycast).step_y = -1;
		(*raycast).side_dist_y = (p->player.pos_y - (*raycast).map_y)
			* (*raycast).delta_dist_y;
	}
	else
	{
		(*raycast).step_y = 1;
		(*raycast).side_dist_y = ((*raycast).map_y + 1.0 - p->player.pos_y)
			* (*raycast).delta_dist_y;
	}
}

/*
	This gives us the distance the ray must travel to reach the next grid line in each direction.
	Note here that the pos_x and pos_y both refer to the player’s position.
*/
void	calculate_delta_distance(t_raycasting *raycast)
{
	if ((*raycast).ray_dir_x == 0)
		(*raycast).delta_dist_x = 1e30;
	else
		(*raycast).delta_dist_x = fabs(1 / (*raycast).ray_dir_x);
	if ((*raycast).ray_dir_y == 0)
		(*raycast).delta_dist_y = 1e30;
	else
		(*raycast).delta_dist_y = fabs(1 / (*raycast).ray_dir_y);
}

/*
	Here i will calculate the direction of the ray based on the player’s direction (dir_x and dir_y),
	the player’s plane (plane_x and plane_y) and the camera plane.
	The camera_x variable represents the x-coordinate of the ray in camera space,
	which is then used to calculate the ray’s direction vector.
*/
int	raycast(t_data *p)
{
	int				x;
	t_raycasting	raycast;
	int				y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		raycast.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		raycast.ray_dir_x = p->player.dir_x + p->player.plane_x
			* raycast.camera_x;
		raycast.ray_dir_y = p->player.dir_y + p->player.plane_y
			* raycast.camera_x;
		raycast.map_x = (int)p->player.pos_x;
		raycast.map_y = (int)p->player.pos_y;
		calculate_delta_distance(&raycast);
		calculate_step_and_side(&raycast, p);
		calculate_dda(p, &raycast);
		calculate_wall_height(&raycast, p);
		y = 0;
		// Draw ceiling
		while (y < raycast.draw_start)
		{
			my_mlx_pixel_put(p, x, y, p->ceiling_rgb);
			y++;
		}
		// Draw wall
		draw_wall_column(p, &raycast, x);
		// Draw floor
		y = raycast.draw_end;
		while (y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(p, x, y, p->floor_rgb);
			y++;
		}
		draw_wall_column(p, &raycast, x);
		x++;
	}
	return (0);
}

int	render_loop(void *param)
{
	t_data *data = (t_data *)param;
	int x, y;
	int ceiling_color;
	int floor_color;

	// Convert RGB strings to integers
	ceiling_color = rgb_to_int(data->ceiling_color);
	floor_color = rgb_to_int(data->floor_color);

	// Clear the image with floor and ceiling colors
	for (y = 0; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, floor_color);
		}
	}

	// Then draw walls
	raycast(data);

	// Put image to window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);

	return (0);
}