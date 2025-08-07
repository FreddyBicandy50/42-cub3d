/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:13:13 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 00:15:59 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.plane_x * MOVE_SPEED;
	new_y = data->player.y - data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.plane_x * MOVE_SPEED;
	new_y = data->player.y + data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}
