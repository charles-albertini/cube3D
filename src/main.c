/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:57:42 by calberti          #+#    #+#             */
/*   Updated: 2025/03/20 16:59:52 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	init_game(t_config *config)
{
	config->mlx = mlx_init(WIN_WIDTH, WIN_WEIGHT, "Cube3D", 1);
	if (!(config->mlx))
		return (printf("Error\nError display\n"), 1);
	get_textures(config);
	get_images(config);
	mlx_key_hook(config->mlx, &my_key_hook, config);
	//ray casting
	mlx_loop(config->mlx);
	mlx_terminate(config->mlx);
	//fonction free et cllean
	return (0);
}


int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		printf("Error\nNeed two arg\n");
		return (1);
	}
	if (!parse_cub_file(argv[1], &config))
		return (1);
	else
		printf("tout est ok !\n");
	if (init_game(&config) == 1)
		return (1);
	clean_config(&config);
	return (0);
}
