/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 00:59:35 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 01:05:34 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->dir_y < 0)
			return (2);
		else
			return (3);
	}
}

static void	setup_texture_coords(t_ray *ray, t_texture *tex)
{
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}

static void	draw_column(t_data *data, t_ray *ray, t_texture *tex, int x)
{
	double	step;
	double	pos;
	int		y;
	int		*texture;

	texture = (int *)tex->img_data;
	step = (double)tex->height / ray->line_height;
	pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)pos;
		pos += step;
		ray->color = texture[tex->width * ray->tex_y + ray->tex_x];
		my_mlx_pixel_put(data, x, y, ray->color);
		y++;
	}
}

void	draw_wall_column(t_data *data, t_ray *ray, int x)
{
	t_texture	*tex;

	ray->tex_index = get_tex_index(ray);
	tex = &data->config.textures[ray->tex_index];
	if (!tex || !tex->img_data)
	{
		ft_putstr_fd("Error\nMissing texture data\n", 2);
		exit(EXIT_FAILURE);
	}
	setup_texture_coords(ray, tex);
	draw_column(data, ray, tex, x);
}
