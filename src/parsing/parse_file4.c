/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:56:24 by ldarsa            #+#    #+#             */
/*   Updated: 2025/08/05 17:34:56 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	error_exit(t_data *game, char *str, char *error_message)
{
	free(str);
	free_given_file(game);
	ft_putendl_fd(error_message, 2);
	close(game->fd);
	exit(EXIT_FAILURE);
}

int	error_exit_matrix(t_data *game, char **matrix, char *error_message)
{
	free_matrix(matrix);
	free_given_file(game);
	ft_putendl_fd(error_message, 2);
	close(game->fd);
	exit(EXIT_FAILURE);
}

int	error_exit_matrix_rgb(t_data *game, char **color, char **matrix,
		char *error_message)
{
	free_matrix(matrix);
	free_matrix(color);
	free_given_file(game);
	ft_putendl_fd(error_message, 2);
	close(game->fd);
	exit(EXIT_FAILURE);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (1);

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}


int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
