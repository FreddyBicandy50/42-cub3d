/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:18 by ldarsa            #+#    #+#             */
/*   Updated: 2025/08/05 17:34:38 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_direction(char *line)
{
	return (!ft_strcmp(line, "NO") || !ft_strcmp(line, "SO") || !ft_strcmp(line,
			"EA") || !ft_strcmp(line, "WE"));
}

int	is_ceil_floor(char *line)
{
	return (!ft_strcmp(line, "F") || !ft_strcmp(line, "C"));
}

int	valid_file_extension(char *filename, char *ext)
{
	size_t	len_filename;
	size_t	len_ext;
	// int		fd;

	if (!filename || !ext)
		return (0);
	len_filename = ft_strlen(filename);
	len_ext = ft_strlen(ext);
	if (len_filename < len_ext)
		return (0);
	if (ft_strncmp(filename + len_filename - len_ext, ext, len_ext) == 0)
		return (1);
	return (0);
}

void	parse_single_direction(char **dest_path, char **splitted,
		t_data *game)
{
	if (*dest_path)
		error_exit_matrix(game, splitted, "ERROR\nDUPLICATE PATH");
	if (!valid_file_extension(splitted[1], ".xpm"))
		error_exit_matrix(game, splitted, "ERROR\nFILE NOT FOUND OR WRONG EXT");
	*dest_path = ft_strdup(splitted[1]);
	if (!*dest_path)
		error_exit_matrix(game, splitted, "ERROR\nMEMORY ALLOCATION FAILED");
}

void	parse_direction(t_data *game, char **splitted)
{
	if (!ft_strcmp(splitted[0], "NO"))
		parse_single_direction(&game->config.no_path, splitted, game);
	else if (!ft_strcmp(splitted[0], "SO"))
		parse_single_direction(&game->config.so_path, splitted, game);
	else if (!ft_strcmp(splitted[0], "WE"))
		parse_single_direction(&game->config.we_path, splitted, game);
	else if (!ft_strcmp(splitted[0], "EA"))
		parse_single_direction(&game->config.ea_path, splitted, game);
}
