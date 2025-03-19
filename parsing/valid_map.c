/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:03:43 by calberti          #+#    #+#             */
/*   Updated: 2025/03/18 20:30:50 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int validate_map(t_config *config)
{
    
    // Vérifier qu'il y a exactement un joueur
    if (!find_player_position(config))
		return (0);
	// Normaliser la carte (rendre toutes les lignes de même longueur)
    if (!normalize_map(config))
		return (0);
    // // Vérifier que la carte est fermée
    if (!check_map_borders(config))
        return (0);
    return (1);
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
		j=0;
        while (config->map.grid[i][j] != '\0')
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
    if (player_count == 0)
    {
        printf("Error\nNo player position found\n");
        return (0);
    }
    
    return (1);
}


int normalize_map(t_config *config)
{
	int i;
	int j;
	int len;
	char **normalize;
	int tab;

	i=0;
	j=0;
	tab = 0;
	normalize = malloc(sizeof(char *) * config->map.height);
	if (!normalize)
        return (0);
	while (i < config->map.height)
	{
		j=0;
		tab = 0;
		len = ft_strlen_width(config->map.grid[i]);
        normalize[i] = malloc(config->map.width + 2);
		while (j < len -1)//on copie les caractere existant
		{
			if (config->map.grid[i][j] == '\t')
				tab++;
			normalize[i][j] = config->map.grid[i][j];
            j++;
		}
		while (j < config->map.width -1 - (tab * 3))//on copie les espace jusqu'a la width max
		{
			normalize[i][j] = ' ';
			j++;
		}
		
		normalize[i][j] = '\n';
		normalize[i][j+1] = '\0';
		i++;
	}
	i = 0;
	while (i < config->map.height)
	{
		free(config->map.grid[i]);
		i++;
	}
	free(config->map.grid);
	config->map.grid = normalize;

	return(1);
}

void	flood_fill_mark(char **map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || x >= width || y >= height || map[y][x] != ' ')
		return;

	map[y][x] = 'O'; // Marquer comme espace extérieur

	flood_fill_mark(map, x + 1, y, height, width);
	flood_fill_mark(map, x - 1, y, height, width);
	flood_fill_mark(map, x, y + 1, height, width);
	flood_fill_mark(map, x, y - 1, height, width);
}

void	mark_outer_spaces(char **map, int height, int width)
{
	int x;
	int y;

	x = 0;
	while (x < width)
	{
		if (map[0][x] == ' ')
			flood_fill_mark(map, x, 0, height, width);
		if (map[height - 1][x] == ' ')
			flood_fill_mark(map, x, height - 1, height, width);
		x++;
	}

	y = 0;
	while (y < height)
	{
		if (map[y][0] == ' ')
			flood_fill_mark(map, 0, y, height, width);
		if (map[y][width - 1] == ' ')
			flood_fill_mark(map, width - 1, y, height, width);
		y++;
	}
}

int	flood_fill(char **map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0); // Si on sort des limites, la map est ouverte

	if (map[y][x] == 'O') // Espace extérieur ignoré
		return (0);

	if (map[y][x] == ' ') // Si un espace interne est atteint, erreur !
		return (0);


	if (map[y][x] == 'V' || map[y][x] == '1') // Déjà visité ou mur
		return (1);

	map[y][x] = 'V'; // Marquer comme visité

	if (!flood_fill(map, x + 1, y, height, width))
		return (0);
	if (!flood_fill(map, x - 1, y, height, width))
		return (0);
	if (!flood_fill(map, x, y + 1, height, width))
		return (0);
	if (!flood_fill(map, x, y - 1, height, width))
		return (0);

	return (1);
}

int	check_map_borders(t_config *config)
{
	char	**copy;
	int		i;
	int		result;

	copy = malloc(sizeof(char *) * config->map.height);
	if (!copy)
		return (0);

	i = 0;
	while (i < config->map.height)
	{
		copy[i] = ft_strdup(config->map.grid[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (0);
		}
		i++;
	}

	mark_outer_spaces(copy, config->map.height, config->map.width);

	result = flood_fill(copy, config->map.player_x, config->map.player_y,
			config->map.height, config->map.width);

	
	// //PRINTF TEST
	// printf("\n--- NORMALIZED MAP ---\n");
    // for (i = 0; i < config->map.height; i++)
	// 	printf("%s", copy[i]);
	
	i = 0;
	while (i < config->map.height)
	{
		free(copy[i]);
		i++;
	}
	free(copy);

	if (!result)
		printf("Error\nMap is not properly closed\n");

	return (result);
}





