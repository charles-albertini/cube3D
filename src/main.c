/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:57:42 by calberti          #+#    #+#             */
/*   Updated: 2025/03/21 15:24:17 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void start_game_engine(t_config *config)
{
    // Initialiser MLX d'abord
    config->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
    if (!config->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize MLX\n");
        clean_config(config);
        exit(EXIT_FAILURE);
    }
    
    // Initialiser les données et charger les textures
    init_all(config);
	init_player_from_config(config);
    get_textures(config);
    
    // Faire un premier rendu
    render_frame(config);
	
    // Ajouter les hooks pour les entrées clavier et le rendu continu
    mlx_key_hook(config->mlx, my_key_hook, config);
    mlx_loop_hook(config->mlx, continuous_render, config);
    
    
    // Lancer la boucle principale (cette fonction est bloquante)
    mlx_loop(config->mlx);
    
    // Cette ligne ne sera exécutée que lorsque la fenêtre sera fermée
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
	else
		printf("tout est ok !\n");
	start_game_engine(&config);
	clean_config(&config);
	return (0);
}
