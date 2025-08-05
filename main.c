/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:25:50 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 22:55:42 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	close_window(t_data *data)
{
	free_game(data);
	exit(0);
	return (0);
}

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.plane_x * MOVE_SPEED;
	new_y = data->player.y - data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.plane_x * MOVE_SPEED;
	new_y = data->player.y + data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)new_y][(int)data->player.x] != '1')
		data->player.y = new_y;
	if (data->map.grid[(int)data->player.y][(int)new_x] != '1')
		data->player.x = new_x;
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = old_dir_x * cos(ROT_SPEED) - data->player.dir_y
		* sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED) + data->player.dir_y
		* cos(ROT_SPEED);
	data->player.plane_x = old_plane_x * cos(ROT_SPEED) - data->player.plane_y
		* sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED) + data->player.plane_y
		* cos(ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = old_dir_x * cos(-ROT_SPEED) - data->player.dir_y
		* sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED) + data->player.dir_y
		* cos(-ROT_SPEED);
	data->player.plane_x = old_plane_x * cos(-ROT_SPEED) - data->player.plane_y
		* sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED) + data->player.plane_y
		* cos(-ROT_SPEED);
}

void	print_matrix(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_config(t_config *config)
{
	printf("Texture Paths:\n");
	printf("NO: %s\n", config->no_path);
	printf("SO: %s\n", config->so_path);
	printf("WE: %s\n", config->we_path);
	printf("EA: %s\n", config->ea_path);
	printf("Floor Color: %d,%d,%d\n", config->floor.r, config->floor.g,
		config->floor.b);
	printf("Ceiling Color: %d,%d,%d\n", config->ceiling.r, config->ceiling.g,
		config->ceiling.b);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("Map (%d lines):\n", map->height);
	printf("----------------------\n");
	while (map->grid && map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	printf("----------------------\n");
}

// Fixed player finding function - THIS is the one you should use
void	find_player_start(t_data *data)
{
	int		i;
	int		j;
	char	dir;

	i = 0;
	while (data->map.grid[i])
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			dir = data->map.grid[i][j];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				// Fix: Pass j as x (column) and i as y (row)
				set_player_start(data, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nNo player start (N/S/E/W) found in map\n", 2);
	exit(1);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 'w')
		move_forward(data);
	else if (keycode == 's')
		move_backward(data);
	else if (keycode == 'a')
		move_left(data);
	else if (keycode == 'd')
		move_right(data);
	else if (keycode == 65361)
		rotate_left(data);
	else if (keycode == 65363)
		rotate_right(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d map.cub\n", 2);
		return (1);
	}
	if (!valid_file_extension(argv[1], ".cub"))
	{
		ft_putstr_fd("Error\nFile must have .cub extension\n", 2);
		return (1);
	}
	init_data(&game);
	game.fd = open(argv[1], O_RDONLY);
	if (game.fd < 0)
	{
		ft_putstr_fd("Error\nFailed to open file\n", 2);
		return (1);
	}
	
	// Parse the file first
	parse_cub_file(&game, game.fd);
	close(game.fd);
	
	// Print debug info BEFORE finding player
	printf("DEBUG: After parsing, before finding player:\n");
	printf("Player at: x=%.2f y=%.2f\n", game.player.x, game.player.y);
	printf("Direction : x=%.2f y=%.2f\n", game.player.dir_x, game.player.dir_y);
	printf("Plane     : x=%.2f y=%.2f\n", game.player.plane_x, game.player.plane_y);
	
	// Print the map to verify it's loaded correctly
	print_map(&game.map);
	
	// Find and set the player position
	find_player_start(&game);
	
	// Print debug info AFTER finding player
	printf("DEBUG: After finding player:\n");
	printf("Player at: x=%.2f y=%.2f\n", game.player.x, game.player.y);
	printf("Direction : x=%.2f y=%.2f\n", game.player.dir_x, game.player.dir_y);
	printf("Plane     : x=%.2f y=%.2f\n", game.player.plane_x, game.player.plane_y);

	create_window(&game);
	
	mlx_loop_hook(game.mlx_ptr, render_loop, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win_ptr, 17, 0, close_window, &game);
	mlx_loop(game.mlx_ptr);
	
	free_game(&game);
	return (0);
}