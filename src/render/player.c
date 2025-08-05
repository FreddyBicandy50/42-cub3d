/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:17:39 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 01:20:27 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_pos_ew(char dir, t_data **data)
{
	if (dir == 'N')
	{
		(*data)->player.dir_x = 0;
		(*data)->player.dir_y = -1;
		(*data)->player.plane_x = -0.66;
		(*data)->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		(*data)->player.dir_x = 0;
		(*data)->player.dir_y = 1;
		(*data)->player.plane_x = 0.66;
		(*data)->player.plane_y = 0;
	}
}

void	init_pos_ns(char dir, t_data **data)
{
	if (dir == 'N')
	{
		(*data)->player.dir_x = 0;
		(*data)->player.dir_y = -1;
		(*data)->player.plane_x = -0.66;
		(*data)->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		(*data)->player.dir_x = 0;
		(*data)->player.dir_y = 1;
		(*data)->player.plane_x = 0.66;
		(*data)->player.plane_y = 0;
	}
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
	init_pos_ns(dir, &data);
	init_pos_ew(dir, &data);
	data->map.grid[row][col] = '0';
}

void	find_player_start(t_data *data)
{
	int		i;
	int		j;
	char	dir;

	i = 0;
	while (data->map.grid[i])
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			dir = data->map.grid[i][j];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				set_player_start(data, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nNo player start (N/S/E/W) found in map\n", 2);
	exit(1);
}
