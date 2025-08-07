/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 00:27:05 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *data)
{
	free_game(data);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
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
