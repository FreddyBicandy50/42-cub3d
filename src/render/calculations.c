/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:50:49 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 01:02:29 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
