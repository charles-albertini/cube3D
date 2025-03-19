/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:01:28 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 14:41:06 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_config(t_config *config)
{
	config->north.path = NULL;
	config->north.img = NULL;
	config->south.path = NULL;
	config->south.img = NULL;
	config->west.path = NULL;
	config->west.img = NULL;
	config->east.path = NULL;
	config->east.img = NULL;
	config->floor.value = -1;
	config->ceiling.value = -1;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->map.player_x = -1;
	config->map.player_y = -1;
	config->map.player_dir = '\0';
}
