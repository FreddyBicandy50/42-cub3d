/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:13:55 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:55 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int	validate_map_walls(t_data *game)
{
	char	**copy;
	int		x;
	int		y;

	copy = copy_map(game->map.grid, game->map.height);
	if (!copy)
		error_exit_matrix(game, copy, "ERROR\nMAP NOT CLOSED");
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_fillable(copy[y][x]))
			{
				if (!flood_fill(copy, x, y, game))
					error_exit_matrix(game, copy, "ERROR\nMAP NOT CLOSED");
			}
			x++;
		}
		y++;
	}
	free_matrix(copy);
	return (1);
}

char	*pad_line(const char *line, int target_width)
{
	char	*padded;
	int		i;
	int		len;

	i = 0;
	len = strlen(line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	while (i < target_width)
	{
		if (i < len)
			padded[i] = line[i];
		else
			padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

void	normalize_map_width(t_data *game)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = pad_line(game->map.grid[i], game->map.width);
		if (!new_grid[i])
		{
			while (--i >= 0)
				free(new_grid[i]);
			free(new_grid);
			return ;
		}
		free(game->map.grid[i]);
		i++;
	}
	new_grid[i] = NULL;
	free(game->map.grid);
	game->map.grid = new_grid;
}
