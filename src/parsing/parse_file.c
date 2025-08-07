/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:33:57 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 20:48:33 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_full_map(t_data *game)
{
	if (!validate_map(game))
	{
		free_given_file(game);
		ft_putendl_fd("ERROR\nINVALID MAP CHARACTER", 2);
		exit(EXIT_FAILURE);
	}
	validate_map_walls(game);
}

int	handle_empty_pre_map(char **line, int is_map_started, int fd)
{
	if (is_empty_line(*line) && !is_map_started)
	{
		free(*line);
		*line = get_next_line(fd);
		return (1);
	}
	return (0);
}

int	process_line(t_data *game, char *line_with_tabs, int *count,
		int *is_map_started)
{
	char	*line;
	char	*no_new_line;
	char	*trimmed_line;

	line = replace_tabs_with_spaces(line_with_tabs);
	free(line_with_tabs);
	no_new_line = ft_strtrim(line, "\n");
	free(line);
	if (!is_map(no_new_line) && (*count) < 6)
	{
		trimmed_line = ft_strtrim(no_new_line, " ");
		free(no_new_line);
		parse_config(game, trimmed_line);
		(*count)++;
	}
	else if (*count == 6)
	{
		*is_map_started = 1;
		parse_map(game, no_new_line);
	}
	else
		error_exit(game, no_new_line, "ERROR\nINVALID MAP INPUT");
	return (1);
}

void	parse_cub_file(t_data *game, int fd)
{
	char	*line_with_tabs;
	int		count;
	int		is_map_started;

	count = 0;
	is_map_started = 0;
	line_with_tabs = get_next_line(fd);
	while (line_with_tabs)
	{
		if (handle_empty_pre_map(&line_with_tabs, is_map_started, fd))
			continue ;
		if (!process_line(game, line_with_tabs, &count, &is_map_started))
			break ;
		line_with_tabs = get_next_line(fd);
	}
	close(game->fd);
	normalize_map_width(game);
	validate_full_map(game);
}
