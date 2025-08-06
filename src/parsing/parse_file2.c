/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:13:30 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 14:35:16 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count == 2);
}

int	check_color_range(t_color color)
{
	if (color.r < 0 || color.r > 255)
		return (0);
	if (color.b < 0 || color.b > 255)
		return (0);
	if (color.g < 0 || color.g > 255)
		return (0);
	return (1);
}

void	parse_ceiling(t_data *game, char **splitted, char **split_rgb)
{
	if (game->config.ceiling.r != -1 && game->config.ceiling.g != -1
		&& game->config.ceiling.b != -1)
		error_exit_matrix_rgb(game, split_rgb, splitted,
			"ERROR\nDUPLICATE COLOR");
	game->config.ceiling.r = ft_atoi(split_rgb[0]);
	game->config.ceiling.g = ft_atoi(split_rgb[1]);
	game->config.ceiling.b = ft_atoi(split_rgb[2]);
	if (!check_color_range(game->config.ceiling))
		error_exit_matrix_rgb(game, split_rgb, splitted,
			"ERROR\nINVALID COLOR RANGE");
}

void	parse_single_color(t_data *game, char **splitted, char **split_rgb)
{
	if (!ft_strcmp(splitted[0], "C"))
		parse_ceiling(game, splitted, split_rgb);
	if (!ft_strcmp(splitted[0], "F"))
	{
		if (game->config.floor.r != -1 && game->config.floor.g != -1
			&& game->config.floor.b != -1)
			error_exit_matrix_rgb(game, split_rgb, splitted,
				"ERROR\nDUPLICATE COLOR");
		game->config.floor.r = ft_atoi(split_rgb[0]);
		game->config.floor.g = ft_atoi(split_rgb[1]);
		game->config.floor.b = ft_atoi(split_rgb[2]);
		if (!check_color_range(game->config.floor))
			error_exit_matrix_rgb(game, split_rgb, splitted,
				"ERROR\nINVALID COLOR RANGE");
	}
}

void	check_digit(t_data *game, char **split_rgb, char **splitted)
{
	int	count;
	int	i;

	count = 0;
	while (count < 3)
	{
		i = 0;
		while (split_rgb[count][i])
		{
			if (!ft_isdigit(split_rgb[count][i]))
				error_exit_matrix_rgb(game, split_rgb, splitted,
					"ERROR\nRGB MUST BE A NUMBER");
			i++;
		}
		count++;
	}
}
