/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:54:36 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/28 16:25:54 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	error_message(char *str)
{
	write(2, str, ft_strlen(str));
	return ;
}

void	exit_and_error(t_data *p)
{
	error_message(p->error_message);
	free_allocated(p);
	exit(EXIT_FAILURE);
}

void	free_allocated(t_data *p)
{
	if (p->map_filename)
		free(p->map_filename);
	if (p->north_filename)
		free(p->north_filename);
	if (p->east_filename)
		free(p->east_filename);
	if (p->west_filename)
		free(p->west_filename);
	if (p->south_filename)
		free(p->south_filename);
	if (p->map_content)
		free_2d_array(p->map_content);
	if (p->floor_color)
		free(p->floor_color);
	if (p->ceiling_color)
		free(p->ceiling_color);
	if (p->map)
		free_2d_array(p->map);
	if (p)
		free(p);
}
