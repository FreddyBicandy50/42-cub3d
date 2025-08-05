/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:33:52 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 17:37:30 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_given_file(t_data *game)
{
	if (game->config.no_path)
		free(game->config.no_path);
	if (game->config.so_path)
		free(game->config.so_path);
	if (game->config.we_path)
		free(game->config.we_path);
	if (game->config.ea_path)
		free(game->config.ea_path);
	if (game->map.grid)
		free_matrix(game->map.grid);
}

void	free_game(t_data *game)
{
	int	i;

	free(game->config.no_path);
	free(game->config.so_path);
	free(game->config.we_path);
	free(game->config.ea_path);
	free_matrix(game->map.grid);
	i = 0;
	while (i < 4)
	{
		if (game->config.textures[i].img_ptr)
			mlx_destroy_image(game->mlx_ptr, game->config.textures[i].img_ptr);
		i++;
	}
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
}
