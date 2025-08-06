/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:25:50 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/06 18:54:03 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	save_text(t_data *data, char *paths[4])
{
	int			i;
	t_texture	*tex;

	i = 0;
	while (i < 4)
	{
		tex = &data->config.textures[i];
		tex->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, paths[i],
				&tex->width, &tex->height);
		if (!tex->img_ptr)
		{
			ft_putstr_fd("Error\nFailed to load texture image\n", 2);
			exit(EXIT_FAILURE);
		}
		tex->img_data = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
				&tex->line_len, &tex->endian);
		if (!tex->img_data)
		{
			ft_putstr_fd("Error\nFailed to access texture pixel data\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_textures(t_data *data)
{
	char	*paths[4];

	paths[0] = data->config.no_path;
	paths[1] = data->config.so_path;
	paths[2] = data->config.we_path;
	paths[3] = data->config.ea_path;
	save_text(data, paths);
}

void	run_game(t_data game)
{
	find_player_start(&game);
	create_window(&game);
	init_textures(&game);
	mlx_loop_hook(game.mlx_ptr, render_loop, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, handle_key_release, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win_ptr, 17, 0, close_window, &game);
	mlx_loop(game.mlx_ptr);
}

static void	print_controls(void)
{
	printf(CYAN "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_data	game;

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
	parse_cub_file(&game, game.fd);
	close(game.fd);
	
	print_controls();
	run_game(game);

	free_game(&game);
	return (0);
}
