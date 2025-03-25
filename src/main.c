/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:57:42 by calberti          #+#    #+#             */
/*   Updated: 2025/03/25 16:15:55 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	start_game_engine(t_config *config)
{
	config->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!config->mlx)
	{
		fprintf(stderr, "Error: Failed to initialize MLX\n");
		clean_config(config);
		exit(EXIT_FAILURE);
	}
	init_all(config);
	init_player_from_config(config);
	get_textures(config);
	render_frame(config);
	mlx_key_hook(config->mlx, my_key_hook, config);
	mlx_loop_hook(config->mlx, continuous_render, config);
	mlx_loop(config->mlx);
	mlx_terminate(config->mlx);
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
	start_game_engine(&config);
	cleanup(&config);
	return (0);
}
