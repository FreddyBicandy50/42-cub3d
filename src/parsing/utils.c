/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:53:15 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/05 23:55:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	init_config(t_data *game)
{
	int	i;

	i = 0;
	game->config.no_path = NULL;
	game->config.so_path = NULL;
	game->config.we_path = NULL;
	game->config.ea_path = NULL;
	game->config.floor.r = -1;
	game->config.floor.g = -1;
	game->config.floor.b = -1;
	game->config.ceiling.r = -1;
	game->config.ceiling.g = -1;
	game->config.ceiling.b = -1;
	while (i < 4)
	{
		game->config.textures[i].img_ptr = NULL;
		game->config.textures[i].img_data = NULL;
		game->config.textures[i].width = 0;
		game->config.textures[i].height = 0;
		game->config.textures[i].bpp = 0;
		game->config.textures[i].line_len = 0;
		game->config.textures[i].endian = 0;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->input.w = 0;
	data->input.a = 0;
	data->input.s = 0;
	data->input.d = 0;
	data->input.left = 0;
	data->input.right = 0;
	data->fd = -1;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->img_data = NULL;
	data->bpp = 0;
	data->line_len = 0;
	data->endian = 0;
	init_config(data);
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
}
