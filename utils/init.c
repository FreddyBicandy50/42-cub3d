/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:28:47 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/01 21:50:50 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_cardinal_direction	ft_get_cardinal_direction(t_raycasting *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

void	init_player(t_data **p)
{
	(*p)->player_dir = '\0';
}

void	initialize_struct(t_data *p)
{
	p->set = 0;
	p->has_no = 0;
	p->has_ea = 0;
	p->has_so = 0;
	p->has_we = 0;
	p->map = NULL;
	p->position = 0;
	p->has_floor = 0;
	p->win_ptr = NULL;
	p->mlx_ptr = NULL;
	p->has_ceiling = 0;
	p->x_coordinate = -1;
	p->y_coordinate = -1;
	init_player(&p);
	p->file_buffer = NULL;
	p->map_content = NULL;
	p->floor_color = NULL;
	p->error_message = NULL;
	p->east_filename = NULL;
	p->ceiling_color = NULL;
	p->west_filename = NULL;
	p->north_filename = NULL;
	p->south_filename = NULL;
}