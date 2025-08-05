/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:13:35 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 02:20:48 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	parse_rgb(t_data *game, char **splitted)
{
	char	**split_rgb;

	if (!count_commas(splitted[1]))
		error_exit_matrix(game, splitted, "ERROR\nINVALID RGB INPUT");
	split_rgb = ft_split(splitted[1], ',');
	if (!split_rgb || !split_rgb[0] || !split_rgb[1] || !split_rgb[2]
		|| split_rgb[3])
		error_exit_matrix_rgb(game, split_rgb, splitted,
			"ERROR\nINVALID RGB INPUT");
	check_digit(game, split_rgb, splitted);
	parse_single_color(game, splitted, split_rgb);
	free_matrix(split_rgb);
}

void	parse_config(t_data *game, char *line)
{
	char	**splitted;

	splitted = ft_split(line, ' ');
	free(line);
	if (!splitted || !splitted[0] || !splitted[1] || splitted[2])
		error_exit_matrix(game, splitted,
			"ERROR\nINCORRECT CONFIGURATION INPUT");
	if (is_direction(splitted[0]))
		parse_direction(game, splitted);
	else if (is_ceil_floor(splitted[0]))
		parse_rgb(game, splitted);
	else
		error_exit_matrix(game, splitted,
			"ERROR\nINCORRECT CONFIGURATION INPUT");
	free_matrix(splitted);
}

static int	count_tabs(char *line)
{
	int	i;
	int	tab_count;

	i = 0;
	tab_count = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			tab_count++;
		i++;
	}
	return (tab_count);
}

static void	fill_tabs(char *line, char *new_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
}

char	*replace_tabs_with_spaces(char *line)
{
	char	*new_line;
	int		tab_count;
	int		length;

	if (!line)
		return (NULL);
	tab_count = count_tabs(line);
	length = ft_strlen(line) + tab_count * 3 + 1;
	new_line = malloc(length);
	if (!new_line)
		return (NULL);
	fill_tabs(line, new_line);
	return (new_line);
}
