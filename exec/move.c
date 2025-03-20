/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:37 by calberti          #+#    #+#             */
/*   Updated: 2025/03/20 16:19:38 by calberti         ###   ########.fr       */
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

	config = param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_up(config);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_right(config);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_down(config);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_left(config);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(config->mlx);
}