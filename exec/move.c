/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:37 by calberti          #+#    #+#             */
/*   Updated: 2025/03/22 16:41:17 by axburin-         ###   ########.fr       */
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

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_config	*config;

	config = (t_config *)param;
	if (keydata.key < 512)
	{
		if (keydata.action == MLX_PRESS)
			config->keys[keydata.key] = 1;
		else if (keydata.action == MLX_RELEASE)
			config->keys[keydata.key] = 0;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(config->mlx);
	}
}

void handle_rotation(t_config *config)
{
	t_player *player = &config->data->player;
	double rotSpeed = 0.03; // Ajustez selon vos besoins

	// Rotation gauche (←)
	if (config->keys[MLX_KEY_RIGHT])
	{
		double oldDirX = player->dir_x;
		double oldPlaneX = player->plane_x;
		player->dir_x = player->dir_x * cos(-rotSpeed) - player->dir_y * sin(-rotSpeed);
		player->dir_y = oldDirX * sin(-rotSpeed) + player->dir_y * cos(-rotSpeed);
		player->plane_x = player->plane_x * cos(-rotSpeed) - player->plane_y * sin(-rotSpeed);
		player->plane_y = oldPlaneX * sin(-rotSpeed) + player->plane_y * cos(-rotSpeed);
	}

	// Rotation droite (→)
	if (config->keys[MLX_KEY_LEFT])
	{
		double oldDirX = player->dir_x;
		double oldPlaneX = player->plane_x;
		player->dir_x = player->dir_x * cos(rotSpeed) - player->dir_y * sin(rotSpeed);
		player->dir_y = oldDirX * sin(rotSpeed) + player->dir_y * cos(rotSpeed);
		player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
		player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
	}
}
