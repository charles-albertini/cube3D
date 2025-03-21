/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:37 by calberti          #+#    #+#             */
/*   Updated: 2025/03/21 15:39:06 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_up(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32 - 1]
		[config->imag->east->instances->x / 32] != '1')
	{
		config->imag->east->instances->y -= 32;
	}
}

void	move_right(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32]
		[config->imag->east->instances->x / 32 + 1] != '1')
	{
		config->imag->east->instances->x += 32;
	}
}

void	move_down(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32 + 1]
		[config->imag->east->instances->x / 32] != '1')
	{
		config->imag->east->instances->y += 32;
	}
}

void	move_left(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32]
		[config->imag->east->instances->x / 32 - 1] != '1')
	{
		config->imag->east->instances->x -= 32;
	}
}

void my_key_hook(mlx_key_data_t keydata, void *param)
{
    t_config *config = (t_config *)param;
    t_player *player = &config->data->player;

    // Gestion de la touche ESC
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(config->mlx);
        return;
    }

    // Déplacements
    if (keydata.key == MLX_KEY_W) // Avancer
    {
        if (keydata.action == MLX_PRESS)
            player->move_y = 1;
        else if (keydata.action == MLX_RELEASE)
            player->move_y = 0;
        player->has_moved = 1;
    }
    if (keydata.key == MLX_KEY_S) // Reculer
    {
        if (keydata.action == MLX_PRESS)
            player->move_y = -1;
        else if (keydata.action == MLX_RELEASE)
            player->move_y = 0;
        player->has_moved = 1;
    }
    if (keydata.key == MLX_KEY_A) // Déplacement gauche
    {
        if (keydata.action == MLX_PRESS)
            player->move_x = -1;
        else if (keydata.action == MLX_RELEASE)
            player->move_x = 0;
        player->has_moved = 1;
    }
    if (keydata.key == MLX_KEY_D) // Déplacement droite
    {
        if (keydata.action == MLX_PRESS)
            player->move_x = 1;
        else if (keydata.action == MLX_RELEASE)
            player->move_x = 0;
        player->has_moved = 1;
    }

    // Rotations de la caméra avec les flèches
    if (keydata.key == MLX_KEY_LEFT) // Rotation gauche
    {
        if (keydata.action == MLX_PRESS)
            player->rotate = -1;
        else if (keydata.action == MLX_RELEASE)
            player->rotate = 0;
        player->has_moved = 1;
    }
    if (keydata.key == MLX_KEY_RIGHT) // Rotation droite
    {
        if (keydata.action == MLX_PRESS)
            player->rotate = 1;
        else if (keydata.action == MLX_RELEASE)
            player->rotate = 0;
        player->has_moved = 1;
    }
}

void update_player_position(t_config *config)
{
    t_player *player = &config->data->player;
    double moveSpeed = 0.05; // Ajustez selon vos besoins
    double rotSpeed = 0.03;  // Ajustez selon vos besoins
    
    if (player->has_moved)
    {
        // Mouvement avant/arrière (W/S)
        if (player->move_y != 0)
        {
            double new_x = player->pos_x + player->dir_x * moveSpeed * player->move_y;
            double new_y = player->pos_y + player->dir_y * moveSpeed * player->move_y;
            
            // Vérification de collision avec les murs
            if (config->data->map[(int)new_y][(int)new_x] != '1')
            {
                player->pos_x = new_x;
                player->pos_y = new_y;
            }
        }
        
        // Mouvement latéral (A/D)
        if (player->move_x != 0)
        {
            double new_x = player->pos_x + player->plane_x * moveSpeed * player->move_x;
            double new_y = player->pos_y + player->plane_y * moveSpeed * player->move_x;
            
            // Vérification de collision avec les murs
            if (config->data->map[(int)new_y][(int)new_x] != '1')
            {
                player->pos_x = new_x;
                player->pos_y = new_y;
            }
        }
        
        // Rotation (Flèches gauche/droite)
        if (player->rotate != 0)
        {
            double oldDirX = player->dir_x;
            double oldPlaneX = player->plane_x;
            
            // Rotation de la direction et du plan de caméra
            double rotFactor = rotSpeed * player->rotate;
            player->dir_x = player->dir_x * cos(rotFactor) - player->dir_y * sin(rotFactor);
            player->dir_y = oldDirX * sin(rotFactor) + player->dir_y * cos(rotFactor);
            player->plane_x = player->plane_x * cos(rotFactor) - player->plane_y * sin(rotFactor);
            player->plane_y = oldPlaneX * sin(rotFactor) + player->plane_y * cos(rotFactor);
        }
        
        player->has_moved = 0; // Réinitialisez pour le prochain cycle
    }
}