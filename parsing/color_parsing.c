/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:13:28 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char_color(char **colors)
{
	int	j;
	int	i;

	j = 0;
	while (colors[j] != NULL)
	{
		i = 0;
		while (colors[j][i] != '\0')
		{
			if (colors[j][i] < '0' || colors[j][i] > '9')
			{
				free_2d_array(colors);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	check_color(char *color, t_data *p)
{
	char	**colors;

	if (!is_valid_color_format(color))
		return (0);
	colors = ft_split(color, ',');
	if (!colors || !recheck_colors(colors)
		|| !check_char_color(colors) || !handle_color(colors, p))
	{
		free_2d_array(colors);
		return (0);
	}
	free_2d_array(colors);
	return (1);
}

int	is_valid_color_format(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isdigit(line[i]) || line[i] == ','))
			return (0);
		i++;
	}
	return (1);
}

int	recheck_colors(char **colors)
{
	int	i;

	i = 0;
	while (colors[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	return (1);
}

int	handle_color(char **colors, t_data *p)
{
	int	i;
	int	nb;

	i = 0;
	while (colors[i] != NULL)
	{
		nb = ft_atoi(colors[i]);
		if (nb > 255 || nb < 0)
		{
			error_message("problem with the color\n");
			free_allocated(p);
			return (0);
		}
		i++;
	}
	return (1);
}
