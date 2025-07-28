/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:49:29 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_column_map(char *line, t_data *p)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != '1')
		{
			p->error_message = "map not enclosed with 1";
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_previous_line(t_data *p, char *line, char *previous_line)
{
	int	len_line;
	int	len_previous;
	int	i;

	len_line = ft_strlen(line);
	len_previous = ft_strlen(previous_line);
	if (len_line >= len_previous)
		return (1);
	else
	{
		i = len_line;
		while (i <= len_previous && previous_line[i] != '\0')
		{
			if (previous_line[i] != '1')
			{
				p->error_message = "border issue in previous line\n";
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_next_line(t_data *p, char *line, char *next_line)
{
	int	len_line;
	int	len_next;
	int	i;

	len_line = ft_strlen(line);
	len_next = ft_strlen(next_line);
	if (len_line >= len_next)
		return (1);
	else
	{
		i = len_line;
		while (i <= len_next && next_line[i] != '\0')
		{
			if (next_line[i] != '1')
			{
				p->error_message = "border issue in next line\n";
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_row_map(char *line, t_data *p)
{
	int	len;

	len = ft_strlen(line);
	if (!process_map(line, p, &len))
		return (0);
	if (p->position > 1)
	{
		p->error_message = "more than 1 coordinate in map\n";
		return (0);
	}
	return (1);
}

int	check_char_map(t_data *p, char *line, int *i)
{
	if (line[*i] != '1' && line[*i] != '0' && line[*i] != 'N'
		&& line[*i] != 'S' && line[*i] != 'W' && line[*i] != 'E')
		return (0);
	if (line[*i] == 'N' || line[*i] == 'S'
		|| line[*i] == 'W' || line[*i] == 'E')
	{
		p->y_coordinate = *i;
		p->position++;
	}
	return (1);
}
