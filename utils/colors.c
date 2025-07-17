/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahroug <adahroug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:42:11 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/07 14:17:43 by adahroug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	floorcolor(t_data *p, char *line)
{
	int	i;

	p->has_floor = 1;
	if (line[1] != ' ')
	{
		printf("error in formating for floorcolor\n");
		return (0);
	}
	i = 2;
	while (line[i] != '\0')
		i++;
	p->floor_color = ft_substr(line, 2, i - 2);
	return (1);
}

int	ceiling(t_data *p, char *line)
{
	int	i;

	p->has_ceiling = 1;
	if (line[1] != ' ')
	{
		printf("error in formating for ceilingcolor\n");
		return (0);
	}
	i = 2;
	while (line[i] != '\0')
		i++;
	p->ceiling_color = ft_substr(line, 2, i - 2);
	return (1);
}

int	parse_line_colors(t_data *p, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (!floorcolor(p, line))
			return (0);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (!ceiling(p, line))
			return (0);
	}
	return (1);
}
