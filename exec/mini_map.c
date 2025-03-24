/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:41:45 by calberti          #+#    #+#             */
/*   Updated: 2025/03/24 14:45:35 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void draw_minimap(t_config *config)
{
    int x, y;
    int map_x, map_y;

    if (!config || !config->data || !config->data->map || !config->mlx || !config->current_image)
        return;

    for (y = 0; y < config->map.height * TILE_SIZE; y++)
    {
        for (x = 0; x < config->map.width * TILE_SIZE; x++)
        {
            mlx_put_pixel(config->current_image, x, y, 0xFFFFFF); // Blanc
        }
    }
    for (y = 0; y < config->map.height; y++)
    {
        for (x = 0; x < config->map.width; x++)
        {
            map_x = x * TILE_SIZE;
            map_y = y * TILE_SIZE;

            if (config->map.grid[y] && config->map.grid[y][x] == '1') // Mur
                for (int i = -2; i <= 2; i++)
                 {
                    for (int j = -2; j <= 2; j++)
                     {
                        if (map_x + i >= 0 && map_x + i + i < config->map.width * TILE_SIZE &&
                            map_y + j >= 0 && map_y + j < config->map.height * TILE_SIZE)
                        {
                            mlx_put_pixel(config->current_image, map_x + i, map_y + j, 0x000000);
                        }
                    }
                }

        }
    }

    // Dessiner un carré rouge pour représenter le joueur
    int player_x = (int)(config->data->player.pos_x * TILE_SIZE);
    int player_y = (int)(config->data->player.pos_y * TILE_SIZE);

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            if (player_x + i >= 0 && player_x + i < config->map.width * TILE_SIZE &&
                player_y + j >= 0 && player_y + j < config->map.height * TILE_SIZE)
            {
                mlx_put_pixel(config->current_image, player_x + i, player_y + j, 0xFF0000); // Rouge
            }
        }
    }

    // Dessiner la direction du joueur
    int line_length = 10;
    int dir_x = player_x + (int)(config->data->player.dir_x * line_length);
    int dir_y = player_y + (int)(config->data->player.dir_y * line_length);
    
    int dx = abs(dir_x - player_x);
    int dy = abs(dir_y - player_y);
    int sx = player_x < dir_x ? 1 : -1;
    int sy = player_y < dir_y ? 1 : -1;
    int err = dx - dy;
    
    while (player_x != dir_x || player_y != dir_y)
    {
        if (player_x >= 0 && player_x < config->map.width * TILE_SIZE &&
            player_y >= 0 && player_y < config->map.height * TILE_SIZE)
        {
            mlx_put_pixel(config->current_image, player_x, player_y, 0xFF0000); // Rouge pour la direction
        }
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; player_x += sx; }
        if (e2 < dx) { err += dx; player_y += sy; }
    }
    mlx_image_to_window(config->mlx, config->current_image, 10, 10);
}