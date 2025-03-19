/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:04:49 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 14:01:10 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void clean_config(t_config *config)
{
	int i;

	i=0;
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
        while (i < config->map.height)
		{
            free(config->map.grid[i]);
			i++;	
		}
        free(config->map.grid);
    }
}