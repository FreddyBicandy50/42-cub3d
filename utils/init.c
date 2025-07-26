/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:28:47 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/25 21:29:43 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_data **p)
{
	(*p)->player.dir = '\0';
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