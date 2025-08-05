/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 00:02:55 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	set_player_start(t_data *data, int row, int col)
{
	char	dir;

	if (row < 0 || col < 0)
	{
		ft_putstr_fd("Error\nPlayer start position not found\n", 2);
		exit(EXIT_FAILURE);
	}
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	dir = data->map.grid[row][col];
	if (dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	data->map.grid[row][col] = '0';
}

void	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		ft_putstr_fd("Error\nMLX init failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!data->win_ptr)
	{
		ft_putstr_fd("Error\nWindow creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img_ptr)
	{
		ft_putstr_fd("Error\nImage creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->line_len, &data->endian);
}
