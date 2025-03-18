/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:03:43 by calberti          #+#    #+#             */
/*   Updated: 2025/03/18 15:46:49 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int validate_map(t_config *config)
{
    // Normaliser la carte (rendre toutes les lignes de même longueur)
    if (!normalize_map(config))
		return (0);
    // Vérifier qu'il y a exactement un joueur
    if (!find_player_position(config))
        return (0);
    
    // Vérifier que la carte est fermée
    if (!check_map_borders(config))
        return (0);
    
    return (1);
}

int normalize_map(t_config *config)
{
	(void)config;
   //Faire fonction pour mettre toute les lignes a la meme longueur
   return(1);
}

int find_player_position(t_config *config)
{
    int i;
	int j;
    int player_count;
	char c;
    
	player_count = 0;
	i =0;
	j = 0;
    while (i < config->map.height)
    {
        while (j < config->map.width)
        {
            c = config->map.grid[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                // Si on a déjà trouvé un joueur, c'est une erreur
                if (player_count > 0)
                {
                    printf("Error\nMultiple player positions found\n");
                    return (0);
                }
                
                // Enregistrer la position et l'orientation du joueur
                config->map.player_x = j;
                config->map.player_y = i;
                config->map.player_dir = c;
                player_count++;
            }
			j++;
        }
		i++;
    }
    
    // Vérifier qu'on a trouvé un joueur
	player_count = 1; // a enlever apres juste pour test
	//
    if (player_count == 0)
    {
        printf("Error\nNo player position found\n");
        return (0);
    }
    
    return (1);
}

int check_map_borders(t_config *config)
{
	(void)config;
    //faire fonction pour checker mur
	return (1);
}

int flood_fill(char **map, int x, int y, int height, int width)
{
	(void)map;
	(void)x;
	(void)y;
	(void)height;
	(void)width;
   //faire fonction flood fill
   return(1);
}