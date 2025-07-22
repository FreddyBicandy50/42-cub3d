/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:30:10 by fbicandy          #+#    #+#             */
/*   Updated: 2025/07/18 15:08:50 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (i++ <= 10)
	{
		j = 1;
		while (j++ <= 10)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, 100 + j, 100 + i,
				0xFFFFFF);
	}
}

void	engine_start(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3d");
	draw(data);
	mlx_loop(data->mlx_ptr);
}
