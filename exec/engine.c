/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:11:35 by calberti          #+#    #+#             */
/*   Updated: 2025/03/22 17:14:44 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	handle_forward_backward(t_config *config, double movespeed)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &config->data->player;
	if (config->keys[MLX_KEY_W])
	{
		new_x = player->pos_x + player->dir_x * movespeed;
		new_y = player->pos_y + player->dir_y * movespeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
	if (config->keys[MLX_KEY_S])
	{
		new_x = player->pos_x - player->dir_x * movespeed;
		new_y = player->pos_y - player->dir_y * movespeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
}

static void	handle_strafe(t_config *config, double movespeed)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &config->data->player;
	if (config->keys[MLX_KEY_A])
	{
		new_x = player->pos_x - player->plane_x * movespeed;
		new_y = player->pos_y - player->plane_y * movespeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
	if (config->keys[MLX_KEY_D])
	{
		new_x = player->pos_x + player->plane_x * movespeed;
		new_y = player->pos_y + player->plane_y * movespeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
}

void	handle_movement(t_config *config)
{
	double	movespeed;

	movespeed = 0.05;
	handle_forward_backward(config, movespeed);
	handle_strafe(config, movespeed);
}

void	continuous_render(void *param)
{
	t_config	*config;

	config = (t_config *)param;
	handle_movement(config);
	handle_rotation(config);
	render_frame(config);
}
