/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:53:15 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/05 21:31:17 by fbicandy         ###   ########.fr       */
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

void	init_data(t_data *game)
{
	game->fd = -1;
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img_ptr = NULL;
	game->img_data = NULL;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	init_config(game);
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
}
