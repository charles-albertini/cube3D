/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:37 by calberti          #+#    #+#             */
/*   Updated: 2025/03/20 23:37:37 by calberti         ###   ########.fr       */
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