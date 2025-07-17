/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:11:51 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_map(t_data *p)
{
	int	map_start;

	if (!open_map(p) || !read_map(p))
		exit_and_error(p);
	close(p->fd);
	p->fd = -1;
	map_start = extract_mapcontent(p);
	if (map_start == -1)
		exit_and_error(p);
	if (!check_mapcontent(p))
		exit_and_error(p);
	copy_map(p, map_start);
	if (!validate_map(p))
		exit_and_error(p);
}

int	parse_line_utils(t_data *p, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!north(p, line))
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!south(p, line))
			return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{	
		if (!west(p, line))
			return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!east(p, line))
			return (0);
	}
	if (!parse_line_colors(p, line))
		return (0);
	return (1);
}

int	parse_line(t_data *p, char *line)
{
	while (*line == ' ')
		line++;
	if (!parse_line_utils(p, line))
		return (0);
	return (1);
}

int	is_map(char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| *line == 'F' || *line == 'C')
		return (0);
	if (*line == '1' || *line == '0' || *line == 'N'
		|| *line == 'S' || *line == 'E' || *line == 'W')
		return (1);
	return (0);
}

int	check_mapcontent(t_data *p)
{
	if (!check_texture(p->north_filename)
		|| !check_texture(p->south_filename)
		|| !check_texture(p->west_filename)
		|| !check_texture(p->east_filename))
	{
		p->error_message = "error with texture of map";
		return (0);
	}
	if (!check_color(p->ceiling_color, p)
		|| !check_color(p->floor_color, p))
	{
		p->error_message = "error with color of map";
		return (0);
	}
	return (1);
}
