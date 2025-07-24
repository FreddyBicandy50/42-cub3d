/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/24 16:42:57 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

void	draw_fov(t_data *data)
{
	int		i;
	float	start_angle;
	float	angle;
	float	end_angle;
	int		len;
	int		end_x;
	int		end_y;

	len = 60;
	start_angle = data->player_dir - DEG_TO_RAD(45); // 90° FOV
	end_angle = data->player_dir + DEG_TO_RAD(45);
	i = 0;
	while (i <= 90) // draw every 5°
	{
		angle = start_angle + DEG_TO_RAD(i);
		end_x = data->player_x + cos(angle) * len;
		end_y = data->player_y + sin(angle) * len;
		draw_line(data, data->player_x, data->player_y, end_x, end_y, 0xAAAAAA);
		i += 5;
	}
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	float	dx;
	float	dy;
	int		steps;
	float	x;
	float	y;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	dx /= steps;
	dy /= steps;
	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_vision_lines(t_data *data)
{
	int		i;
	float	angle;
	int		len;
	int		end_x;
	int		end_y;

	len = 60;
	i = 0;
	while (i < 360)
	{
		angle = i * (3.14 / 180); // convert degrees to radians
		end_x = data->player_x + cos(angle) * len;
		end_y = data->player_y + sin(angle) * len;
		draw_line(data, data->player_x, data->player_y, end_x, end_y, 0xAAAAAA);
		i += 30; // every 30 degrees (12 lines)
	}
}

void	draw(t_data *data)
{
	int	i;
	int	j;

	// Draw the player as a square
	i = data->player_x - 5;
	while (i <= data->player_x + 5)
	{
		j = data->player_y - 5;
		while (j <= data->player_y + 5)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	draw_vision_lines(data);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	else if (keycode == XK_w)
		data->player_y -= 5;
	else if (keycode == XK_s)
		data->player_y += 5;
	else if (keycode == XK_a)
		data->player_x -= 5;
	else if (keycode == XK_d)
		data->player_x += 5;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

void	engine_start(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3d");
	data->player_x = 100;
	data->player_y = 100;
	draw(data);
	mlx_key_hook(data->win_ptr, key_press, data);
	mlx_loop(data->mlx_ptr);
}
