/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:24:20 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_map(t_data *p)
{
	int	i;

	i = 0;
	if (!check_column_map(p->map[0], p))
		return (0);
	while (p->map[i] != NULL)
	{
		trimwhitespace_str(p->map[i]);
		if (i > 0 && p->map[i] != NULL && p->map[i + 1] != NULL)
		{
			if (!check_previous_line(p, p->map[i], p->map[i - 1])
				|| (!check_next_line(p, p->map[i], p->map[i + 1])))
				return (0);
		}
		if (!check_row_map(p->map[i], p))
			return (0);
		if (p->y_coordinate != -1)
			set_x_coordinate(p, i);
		i++;
	}
	if (!check_column_map(p->map[i - 1], p)
		|| !is_correct_coordinate(p)
		|| !flood_fill_check(p))
		return (0);
	return (1);
}

int	is_correct_coordinate(t_data *p)
{
	if (p->position != 1 || p->x_coordinate == -1)
	{
		p->error_message = "wrong position or coordinate\n";
		return (0);
	}
	return (1);
}

void	set_x_coordinate(t_data *p, int i)
{
	if (p->set == 1)
		return ;
	p->x_coordinate = i;
	p->set = 1;
	return ;
}

int	process_map(char *line, t_data *p, int *len)
{
	int	i;

	i = 0;
	if (*len == 0)
		return (0);
	if (!recheck_mapwalls(p, line, len))
		return (0);
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != '1' && line[*len - 1] != '1')
		{
			p->error_message = "borders wrong in map\n";
			return (0);
		}
		if (!check_char_map(p, line, &i))
		{
			p->error_message = "wrong char in map\n";
			return (0);
		}
		i++;
	}
	return (1);
}

int	recheck_mapwalls(t_data *p, char *line, int *len)
{
	if (line[0] != '1' && line[0] != ' ')
	{
		p->error_message = "map line doesn't start with wall";
		return (0);
	}
	if (line[*len - 1] != '1' && line[*len - 1] != ' ')
	{
		p->error_message = "map line doesn't end with wall";
		return (0);
	}
	return (1);
}
