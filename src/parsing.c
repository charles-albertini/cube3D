/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:01:17 by calberti          #+#    #+#             */
/*   Updated: 2025/03/17 20:38:36 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


//OUVRIR ET LIRE LE FICHIER
int parse_file(char *filename, t_config *config)
{
    int fd;
    char *line;
	int empty;
    
	empty = 0;
    // Initialiser la configuration avec des valeurs par défaut
    init_config(config);
	
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nNo such file or directory\n");
        return (0);
    }
    
    line = get_next_line(fd);
    // Lire le fichier ligne par ligne
    while (line)
    {
		empty = 1;
		//cas ou map pas a la fin du fichier
		if (config->map.grid != NULL && is_empty_line(line))
        {
			printf("Error\nMap not at the end\n");
    		return (0);
		}
        if (!parse_line(line, config))
        {
            free(line);
            close(fd);
            return (0);
        }
        free(line);
		line = get_next_line(fd);
    }
    close(fd);
	if (empty == 0)
	{
		printf("Error\nEmpty file\n");
    	return (0);
	}
		
    // Vérifier que la configuration est complète et valide
    return (validate_config(config));
}
//PARSER CHAQUE LIGNE
int parse_line(char *line, t_config *config)
{
    // Ignorer les lignes vides
    if (is_empty_line(line))
		return (1);
    // Si on a déjà commencé à parser la carte, continuer avec la carte
    if (config->map.grid != NULL)
        return (parse_map_line(line, config));
    
    // Sinon, essayer de parser un élément de configuration
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (config->north.path != NULL)
		{
			printf("Error\nDuplicat textures: %s\n", line);
    		return (0);
		}
        return (parse_texture(line + 3, &config->north));
	}
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (config->south.path != NULL)
		{
			printf("Error\nDuplicat textures: %s\n", line);
    		return (0);
		}	
        return (parse_texture(line + 3, &config->south));
	}
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (config->west.path != NULL)
		{
			printf("Error\nDuplicat textures: %s\n", line);
    		return (0);
		}
        return (parse_texture(line + 3, &config->west));
	}
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (config->east.path != NULL)
		{
			printf("Error\nDuplicat textures: %s\n", line);
    		return (0);
		}
        return (parse_texture(line + 3, &config->east));
	}
    else if (line[0] == 'F' && line[1] == ' ')
	{
		if (config->floor.value != -1)
		{
			printf("Error\nDuplicat colors\n");
    		return (0);
		}
        return (parse_color(line + 2, &config->floor));
	}
    else if (line[0] == 'C' && line[1] == ' ')
	{
		if (config->ceiling.value != -1)
		{
			printf("Error\nDuplicat colors\n");
    		return (0);
		}
        return (parse_color(line + 2, &config->ceiling));
	}
    else if (is_map_line(line))
        return (start_map_parsing(line, config));
    
    // Si on arrive ici, la ligne n'est pas reconnue
    printf("Error\nInvalid line: %s\n", line);
    return (0);
}
//PARSER LES TEXTURE
int parse_texture(char *path, t_texture *texture)
{
	int len;
	// Vérifier l'extension du fichier
    len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\n' || 
			path[len - 1] == '\t'))
        path[--len] = '\0';
	len = ft_strlen(path);
    if (len < 4 || ft_strcmp(path + len - 4, ".png") != 0)
    {
        printf("Error\nInvalid file extension: %s\n", path);
        return (0);
    }
    // Supprimer les espaces au début
    while (*path == ' ')
        path++;
    
    // Vérifier que le chemin n'est pas vide
    if (*path == '\0')
    {
        printf("Error\nEmpty texture path\n");
        return (0);
    }
    
    // Copier le chemin
    texture->path = ft_strdup(path);
    if (texture->path == NULL)
    {
        printf("Error\nMemory allocation failed\n");
        return (0);
    }
    
    return (1);
}
//PARSER LES COULEURS
int parse_color(char *str, t_color *color)
{
    char **parts;
    int r, g, b;
    
    // Supprimer les espaces au début
    while (*str == ' ')
        str++;
    
    // Diviser la chaîne par les virgules
    parts = ft_split(str, ',');
    if (parts == NULL)
        return (0);
    
    // Vérifier qu'il y a exactement 3 parties
    if (ft_arrlen(parts) != 3)
    {
        free_array(parts);
        printf("Error\nInvalid color format: %s\n", str);
        return (0);
    }
	if(is_all_num(parts[0]) || is_all_num(parts[1]) || is_all_num(parts[2]))
	{
        free_array(parts);
        printf("Error\nWrong values\n");
        return (0);
	}
    // Convertir chaque partie en entier et vérifier les limites
    r = ft_atoi(parts[0]);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);
    
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_array(parts);
        printf("Error\nColor values must be between 0 and 255\n");
        return (0);
    }
    
    // Stocker les valeurs
    color->r = r;
    color->g = g;
    color->b = b;
    color->value = (r << 16) | (g << 8) | b;
	
    free_array(parts);
    return (1);
}

//PARSING PRINCIPAL
int parse_cub_file(char *filename, t_config *config)
{
    // Vérifier l'extension du fichier
    int len = ft_strlen(filename);
    if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
    {
        printf("Error\nInvalid file extension: %s\n", filename);
        return (0);
    }
    
    // Parser le fichier
    if (!parse_file(filename, config))
    {
        clean_config(config);
        return (0);
    }
    
    return (1);
}