/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:18:26 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/17 16:06:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	north(t_data *p, char *line)
{
	int	i;
	int	len;
	int	fd;

	p->has_no = 1;
	len = 0;
	i = 3;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		len++;
		i++;
	}
	p->north_filename = ft_substr(line, 3, len);
	fd = open(p->north_filename, O_RDONLY);
	if (fd == -1)
	{
		p->error_message = "couldnt open north filename\n";
		return (0);
	}
	close(fd);
	return (1);
}

int	south(t_data *p, char *line)
{
	int	i;
	int	len;
	int	fd;

	p->has_so = 1;
	len = 0;
	i = 3;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		len++;
		i++;
	}
	p->south_filename = ft_substr(line, 3, len);
	fd = open(p->south_filename, O_RDONLY);
	if (fd == -1)
	{
		p->error_message = "couldnt open south filename\n";
		return (0);
	}
	close(fd);
	return (1);
}

int	east(t_data *p, char *line)
{
	int	i;
	int	len;
	int	fd;

	p->has_ea = 1;
	len = 0;
	i = 3;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		len++;
		i++;
	}
	p->east_filename = ft_substr(line, 3, len);
	fd = open(p->east_filename, O_RDONLY);
	if (fd == -1)
	{
		p->error_message = "couldnt open east filename\n";
		return (0);
	}
	close(fd);
	return (1);
}

int	west(t_data *p, char *line)
{
	int	i;
	int	len;
	int	fd;

	p->has_we = 1;
	len = 0;
	i = 3;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		len++;
		i++;
	}
	p->west_filename = ft_substr(line, 3, len);
	fd = open(p->west_filename, O_RDONLY);
	if (fd == -1)
	{
		p->error_message = "couldnt open west filename\n";
		return (0);
	}
	close(fd);
	return (1);
}
