/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:18:52 by ldarsa            #+#    #+#             */
/*   Updated: 2025/08/05 17:35:21 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_map(t_data *game)
{
	int		player_count;
	int		row;
	int		col;
	char	c;

	player_count = 0;
	row = 0;
	while (row < game->map.height)
	{
		col = 0;
		while (col < game->map.width)
		{
			c = game->map.grid[row][col];
			if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				return (0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			col++;
		}
		row++;
	}
	return (player_count == 1);
}

static char	**create_new_grid(t_data *game)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (game->map.height + 2));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = game->map.grid[i];
		i++;
	}
	return (new_grid);
}

static int	add_line_to_grid(t_data *game, char **new_grid, char *line)
{
	char	*padded;

	padded = pad_line(line, game->map.width);
	if (!padded)
	{
		free(new_grid);
		return (0);
	}
	new_grid[game->map.height] = padded;
	new_grid[game->map.height + 1] = NULL;
	return (1);
}

static void	update_map_width(t_data *game, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > game->map.width)
		game->map.width = len;
}

void	parse_map(t_data *game, char *line)
{
	char	**new_grid;

	update_map_width(game, line);
	new_grid = create_new_grid(game);
	if (!new_grid)
		return ;
	if (!add_line_to_grid(game, new_grid, line))
		return ;
	if (game->map.grid)
		free(game->map.grid);
	game->map.grid = new_grid;
	game->map.height++;
	free(line);
}
