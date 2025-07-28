/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:57:40 by adahroug          #+#    #+#             */
/*   Updated: 2025/07/28 17:32:29 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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
	t_data	*p;

	if (argc != 2)
	{
		error_message("Error, wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	p = malloc(sizeof(t_data));
	if (!p)
		return (1);
	initialize_struct(p);
	p->map_filename = ft_strdup(argv[1]);
	parse_map(p);
	create_window(p);
	init_textures(p);
	cub3d_controls();
	mlx_loop_hook(p->mlx_ptr, rendering, p);
	mlx_loop(p->mlx_ptr);
	free_allocated(p);
	return (0);
}
