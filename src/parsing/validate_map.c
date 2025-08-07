/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:13:51 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 14:35:25 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_fillable(char c)
{
	return (c == '0' || is_player_char(c));
}

char	**copy_map(char **src, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(char **map, int x, int y, t_data *game)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (!is_fillable(map[y][x]))
		return (1);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, game))
		return (0);
	if (!flood_fill(map, x - 1, y, game))
		return (0);
	if (!flood_fill(map, x, y + 1, game))
		return (0);
	if (!flood_fill(map, x, y - 1, game))
		return (0);
	return (1);
}
