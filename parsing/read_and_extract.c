/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:52:52 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_map(t_data *p)
{
	p->fd = open(p->map_filename, O_RDONLY);
	if (p->fd == -1)
	{
		p->error_message = "couldnt open map\n";
		return (0);
	}
	return (1);
}

int	read_map(t_data *p)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;

	p->bytes_read = read(p->fd, buffer, BUFFER_SIZE);
	while (p->bytes_read > 0)
	{
		buffer[p->bytes_read] = '\0';
		if (p->file_buffer == NULL)
			p->file_buffer = ft_strdup(buffer);
		else
		{
			tmp = p->file_buffer;
			p->file_buffer = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		p->bytes_read = read(p->fd, buffer, BUFFER_SIZE);
	}
	if (p->bytes_read < 0)
	{
		p->error_message = "not reading from map\n";
		return (0);
	}
	p->map_content = ft_split(p->file_buffer, '\n');
	free(p->file_buffer);
	return (1);
}

int	extract_mapcontent(t_data *p)
{
	int	i;

	i = 0;
	while (p->map_content[i] != NULL)
	{
		trimwhitespace_str(p->map_content[i]);
		if (is_map(p->map_content[i]))
			break ;
		if (!parse_line(p, p->map_content[i]))
			return (-1);
		i++;
	}
	if (!p->has_no || !p->has_so || !p->has_we || !p->has_ea
		|| !p->has_ceiling || !p->has_floor)
	{
		printf("%d\n", p->has_no);
		printf("%d\n", p->has_so);
		printf("%d\n", p->has_we);
		printf("%d\n", p->has_ea);
		printf("%d\n", p->has_floor);
		printf("%d\n", p->has_ceiling);
		p->error_message = "error, attribute missing\n";
		return (-1);
	}
	return (i);
}
