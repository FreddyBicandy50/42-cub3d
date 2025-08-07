/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:18:06 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 00:23:41 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_controls(t_data *data)
{
	if (data->input.w && !data->input.s)
		move_forward(data);
	else if (data->input.s && !data->input.w)
		move_backward(data);
	if (data->input.a && !data->input.d)
		move_left(data);
	else if (data->input.d && !data->input.a)
		move_right(data);
	if (data->input.left && !data->input.right)
		rotate_left(data);
	else if (data->input.right && !data->input.left)
		rotate_right(data);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->input.w = 0;
	else if (keycode == 'a')
		data->input.a = 0;
	else if (keycode == 's')
		data->input.s = 0;
	else if (keycode == 'd')
		data->input.d = 0;
	else if (keycode == 65361)
		data->input.left = 0;
	else if (keycode == 65363)
		data->input.right = 0;
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 'w')
		data->input.w = 1;
	else if (keycode == 'a')
		data->input.a = 1;
	else if (keycode == 's')
		data->input.s = 1;
	else if (keycode == 'd')
		data->input.d = 1;
	else if (keycode == 65361)
		data->input.left = 1;
	else if (keycode == 65363)
		data->input.right = 1;
	return (0);
}
