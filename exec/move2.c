/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:26:25 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/25 16:19:43 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (config->movespeed == 0.15)
			config->movespeed = 0.05;
		else if (config->movespeed == 0.05)
			config->movespeed = 0.15;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(config->mlx);
	}
}

static void	rotate_right(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot_speed)
		- player->dir_y * sin(-rot_speed);
	player->dir_y = old_dir_x * sin(-rot_speed)
		+ player->dir_y * cos(-rot_speed);
	player->plane_x = player->plane_x * cos(-rot_speed)
		- player->plane_y * sin(-rot_speed);
	player->plane_y = old_plane_x * sin(-rot_speed)
		+ player->plane_y * cos(-rot_speed);
}

static void	rotate_left(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

void	handle_rotation(t_config *config)
{
	t_player	*player;
	double		rot_speed;

	player = &config->data->player;
	rot_speed = 0.03;
	if (config->keys[MLX_KEY_RIGHT])
		rotate_right(player, rot_speed);
	if (config->keys[MLX_KEY_LEFT])
		rotate_left(player, rot_speed);
}
