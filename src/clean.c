/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:04:49 by calberti          #+#    #+#             */
/*   Updated: 2025/03/15 13:03:31 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void clean_config(t_config *config)
{
    // Libérer les chemins de textures
    if (config->north.path)
        free(config->north.path);
    if (config->south.path)
        free(config->south.path);
    if (config->west.path)
        free(config->west.path);
    if (config->east.path)
        free(config->east.path);
    
    // Libérer la carte
    if (config->map.grid)
    {
        for (int i = 0; i < config->map.height; i++)
            free(config->map.grid[i]);
        free(config->map.grid);
    }
}