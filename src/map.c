/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:36:58 by calberti          #+#    #+#             */
/*   Updated: 2025/03/18 17:05:33 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

//DETECTER LE DEBUT DE LA CARTE
int is_map_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\t' &&
            line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' &&
			line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int start_map_parsing(char *first_line, t_config *config)
{
    // Allouer de la mémoire pour la première ligne
    config->map.grid = malloc(sizeof(char *));
    if (config->map.grid == NULL)
        return (0);
    
    config->map.grid[0] = ft_strdup(first_line);
    if (config->map.grid[0] == NULL)
    {
        free(config->map.grid);
        config->map.grid = NULL;
        return (0);
    }
    
    config->map.height = 1;
    config->map.width = ft_strlen(first_line);
    
    return (1);
}

int parse_map_line(char *line, t_config *config)
{
    char **new_grid;
    int i;
    
	i =0;
    // Si c'est une ligne vide après le début de la carte, c'est une erreur
    if (is_empty_line(line))
    {
        printf("Error\nEmpty line in map\n");
        return (0);
    }
    
    // Vérifier que la ligne contient uniquement des caractères valides
    if (!is_map_line(line))
    {
        printf("Error\nInvalid character in map\n");
        return (0);
    }
    
    // Allouer de la mémoire pour la nouvelle grille
    new_grid = malloc(sizeof(char *) * (config->map.height + 1));
    if (new_grid == NULL)
        return (0);
    
    // Copier les lignes existantes
    while (i < config->map.height)
	{
        new_grid[i] = config->map.grid[i];
		i++;
	}
    
    // Ajouter la nouvelle ligne
    new_grid[config->map.height] = ft_strdup(line);
    if (new_grid[config->map.height] == NULL)
    {
        free(new_grid);
        return (0);
    }
    
    // Mettre à jour la largeur si nécessaire
    int line_len = ft_strlen(line);
    if (line_len > config->map.width)
        config->map.width = line_len;
    
    // Libérer l'ancienne grille et la remplacer par la nouvelle
    free(config->map.grid);
    config->map.grid = new_grid;
    config->map.height++;
    
    return (1);
}

//VALIDER LA CONFIGURATION
int validate_config(t_config *config)
{
	//faire un premier if ou on verifie les deux au cas ou 
	//il manque les deux (color et textur) 
	
    // Vérifier que toutes les textures sont définies
    if (config->north.path == NULL || config->south.path == NULL ||
        config->west.path == NULL || config->east.path == NULL)
    {
        printf("Error\nMissing texture(s)\n");
        return (0);
    }
    
    // Vérifier que les couleurs sont définies
    if (config->floor.value == -1 || config->ceiling.value == -1)
    {
        printf("Error\nMissing color(s)\n");
        return (0);
    }

    // Vérifier que la carte est définie
    if (config->map.grid == NULL)
    {
        printf("Error\nNo map found\n");
        return (0);
    }
    
    // Vérifier que la carte est fermée et contient un joueur
    return (validate_map(config));
}

