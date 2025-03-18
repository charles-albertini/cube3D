/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:57:42 by calberti          #+#    #+#             */
/*   Updated: 2025/03/17 14:25:44 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int main(int argc, char **argv)
{
    t_config config;
    
    // Vérifier le nombre d'arguments
    if (argc != 2)
    {
        printf("Error\nNeed two arg\n");
        return (1);
    }
    
    // Parser le fichier .cub
    if (!parse_cub_file(argv[1], &config))
        return (1);
	else
		printf("tout est ok !\n");
    
    // Initialiser la minilibX et lancer le jeu
    // ...
    
    // Nettoyer avant de quitter
    clean_config(&config);
    return (0);
}