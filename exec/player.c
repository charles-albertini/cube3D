/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:10:43 by calberti          #+#    #+#             */
/*   Updated: 2025/03/21 15:40:53 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../cub3D.h"

void init_player_from_config(t_config *config)
{
    config->data->player.pos_x = config->map.player_x + 0.5; // Centre du carré
    config->data->player.pos_y = config->map.player_y + 0.5;
    config->data->player.has_moved = 0;
    config->data->player.move_x = 0;
    config->data->player.move_y = 0;
    config->data->player.rotate = 0;
    
    // Initialiser la direction et le plan de la caméra selon l'orientation du joueur
    if (config->map.player_dir == 'N')
    {
        config->data->player.dir_x = -1.0;
        config->data->player.dir_y = 0.0;
        config->data->player.plane_x = 0.0;
        config->data->player.plane_y = 0.66;
    }
    else if (config->map.player_dir == 'S')
    {
        config->data->player.dir_x = 1.0;
        config->data->player.dir_y = 0.0;
        config->data->player.plane_x = 0.0;
        config->data->player.plane_y = -0.66;
    }
    else if (config->map.player_dir == 'E')
    {
        config->data->player.dir_x = 0.0;
        config->data->player.dir_y = 1.0;
        config->data->player.plane_x = 0.66;
        config->data->player.plane_y = 0.0;
    }
    else if (config->map.player_dir == 'W')
    {
        config->data->player.dir_x = 0.0;
        config->data->player.dir_y = -1.0;
        config->data->player.plane_x = -0.66;
        config->data->player.plane_y = 0.0;
    }
}

void move_player(t_config *config)
{
    double move_speed = 30;
    double rot_speed = 0.05;
    int new_x, new_y;
    
    // Avancer
    if (config->data->player.move_y == 1)
    {
        new_x = (int)(config->data->player.pos_x + config->data->player.dir_x * move_speed);
        new_y = (int)(config->data->player.pos_y + config->data->player.dir_y * move_speed);
        
        // Vérifier les limites de la carte avant déplacement
        if (new_x >= 0 && new_x < config->map.height && 
            new_y >= 0 && new_y < config->map.width)
        {
            if (config->map.grid[new_x][new_y] != '1')
            {
                config->data->player.pos_x += config->data->player.dir_x * move_speed;
                config->data->player.pos_y += config->data->player.dir_y * move_speed;
            }
        }
    }
    
    // Reculer
    if (config->data->player.move_y == -1)
    {
        new_x = (int)(config->data->player.pos_x - config->data->player.dir_x * move_speed);
        new_y = (int)(config->data->player.pos_y - config->data->player.dir_y * move_speed);
        
        if (new_x >= 0 && new_x < config->map.height && 
            new_y >= 0 && new_y < config->map.width)
        {
            if (config->map.grid[new_x][new_y] != '1')
            {
                config->data->player.pos_x -= config->data->player.dir_x * move_speed;
                config->data->player.pos_y -= config->data->player.dir_y * move_speed;
            }
        }
    }
    
    // Déplacer à gauche
    if (config->data->player.move_x == -1)
    {
        new_x = (int)(config->data->player.pos_x - config->data->player.plane_x * move_speed);
        new_y = (int)(config->data->player.pos_y - config->data->player.plane_y * move_speed);
        
        if (new_x >= 0 && new_x < config->map.height && 
            new_y >= 0 && new_y < config->map.width)
        {
            if (config->map.grid[new_x][new_y] != '1')
            {
                config->data->player.pos_x -= config->data->player.plane_x * move_speed;
                config->data->player.pos_y -= config->data->player.plane_y * move_speed;
            }
        }
    }
    
    // Déplacer à droite
    if (config->data->player.move_x == 1)
    {
        new_x = (int)(config->data->player.pos_x + config->data->player.plane_x * move_speed);
        new_y = (int)(config->data->player.pos_y + config->data->player.plane_y * move_speed);
        
        if (new_x >= 0 && new_x < config->map.height && 
            new_y >= 0 && new_y < config->map.width)
        {
            if (config->map.grid[new_x][new_y] != '1')
            {
                config->data->player.pos_x += config->data->player.plane_x * move_speed;
                config->data->player.pos_y += config->data->player.plane_y * move_speed;
            }
        }
    }
    
    // Rotation gauche/droite
    if (config->data->player.rotate != 0)
    {
        double old_dir_x = config->data->player.dir_x;
        double old_plane_x = config->data->player.plane_x;
        
        rot_speed *= config->data->player.rotate;
        
        // Rotation de la direction et du plan de caméra
        config->data->player.dir_x = config->data->player.dir_x * cos(rot_speed) - config->data->player.dir_y * sin(rot_speed);
        config->data->player.dir_y = old_dir_x * sin(rot_speed) + config->data->player.dir_y * cos(rot_speed);
        config->data->player.plane_x = config->data->player.plane_x * cos(rot_speed) - config->data->player.plane_y * sin(rot_speed);
        config->data->player.plane_y = old_plane_x * sin(rot_speed) + config->data->player.plane_y * cos(rot_speed);
    }
}