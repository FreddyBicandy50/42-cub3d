/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahroug <adahroug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:02:05 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/06 21:13:55 by adahroug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_out_of_bounds(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	if (map[x] == NULL || y >= (int)ft_strlen(map[x]))
		return (1);
	return (0);
}

int	is_invalid_tile(char tile)
{
	return (tile == ' ' || tile == '\0');
}

void	fill(char **map, int x, int y, int *error)
{
	if (*error)
		return ;
	if (is_out_of_bounds(map, x, y) || is_invalid_tile(map[x][y]))
	{
		*error = 1;
		return ;
	}
	if (map[x][y] == '1' || map[x][y] == 'F')
		return ;
	map[x][y] = 'F';
	fill(map, x + 1, y, error);
	fill(map, x - 1, y, error);
	fill(map, x, y + 1, error);
	fill(map, x, y - 1, error);
}

int	flood_fill_check(t_data *p)
{
	char	**map_copy;
	int		error;

	error = 0;
	map_copy = malloc_2d_copy(p->map);
	if (!map_copy)
	{
		p->error_message = "flood fill failed to allocate map copy\n";
		return (0);
	}
	fill(map_copy, p->x_coordinate, p->y_coordinate, &error);
	free_2d_array(map_copy);
	if (error)
	{
		p->error_message = "map is not enclosed properly (flood fill failed)\n";
		return (0);
	}
	return (1);
}
