/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:23:23 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_texture(char *filename)
{
	int		fd;
	int		len;
	char	*extension;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
	{
		close(fd);
		return (0);
	}
	extension = ft_substr(filename, len - 4, 4);
	if ((ft_strcmp(extension, ".xpm") != 0)
		&& (ft_strcmp(extension, ".png") != 0))
	{
		close(fd);
		free(extension);
		return (0);
	}
	close(fd);
	free(extension);
	return (1);
}

int	copy_map_lines(t_data *p, int map_start, int finish)
{
	int	index;

	index = 0;
	while (map_start < finish)
	{
		p->map[index] = malloc((ft_strlen(p->map_content[map_start]) + 1)
				* sizeof(char));
		if (!p->map[index])
		{
			while (--index >= 0)
				free(p->map[index]);
			free(p->map);
			return (0);
		}
		ft_strcpy(p->map[index], p->map_content[map_start]);
		index++;
		map_start++;
	}
	p->map[index] = NULL;
	return (1);
}

void	copy_map(t_data *p, int map_start)
{
	int	finish;

	finish = map_start;
	while (p->map_content[finish] != NULL)
		finish++;
	p->map = malloc((finish - map_start + 1) * sizeof(char *));
	if (!p->map)
		return ;
	if (!copy_map_lines(p, map_start, finish))
		return ;
}

void	trimwhitespace_str(char *line)
{
	int	end;

	end = ft_strlen(line) - 1;
	while (end >= 0 && line[end] == ' ')
		end--;
	line[end + 1] = '\0';
	return ;
}
