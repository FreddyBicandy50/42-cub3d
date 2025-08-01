/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:57:40 by adahroug          #+#    #+#             */
/*   Updated: 2025/08/01 22:49:38 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_allocated(data);
		exit(0);
	}
	// Add movement handling here later
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_allocated(data);
	exit(0);
	return (0);
}
void	cub3d_controls(void)
{
	printf(BRIGHT_RED "\n");
	printf("░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(YELLOW "\tW" RESET ": move forward\t");
	printf(YELLOW "\tS" RESET ": move backward\n");
	printf(YELLOW "\tA" RESET ": strafe left\t");
	printf(YELLOW "\tD" RESET ": strafe right\n");
	printf(YELLOW "\t<" RESET ": rotate left\t");
	printf(YELLOW "\t>" RESET ": rotate right\n");
	printf("\n");
	return ;
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	initialize_struct(data);
	data->map_filename = ft_strdup(argv[1]);

	parse_map(data);
	create_window(data);
	init_textures(data);
	// Add after init_textures(data); in main.c
	printf("Debug: Texture loading status:\n");
	printf("North: %p (file: %s)\n", data->north_img, data->north_filename);
	printf("South: %p (file: %s)\n", data->south_img, data->south_filename);
	printf("East: %p (file: %s)\n", data->east_img, data->east_filename);
	printf("West: %p (file: %s)\n", data->west_img, data->west_filename);
	printf("Player pos: %f, %f\n", data->player.pos_x, data->player.pos_y);
	set_player_start(data);

	// Remove the test red square code

	// Initial render
	render_loop(data);

	// Set up event hooks (you'll need to implement these)
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx_ptr, render_loop, data);

	// Print controls
	cub3d_controls();

	mlx_loop(data->mlx_ptr);

	return (0);
}