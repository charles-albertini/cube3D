/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:37:11 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/23 12:43:06 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// Gère la rotation vers la droite
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

// Gère la rotation vers la gauche
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

// Gère les rotations du joueur
void	handle_rotation2(t_config *config)
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

// Gère les déplacements avant/arrière
void	move_forward_backward(t_config *config, double move_speed)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &config->data->player;
	if (config->keys[MLX_KEY_W])
	{
		new_x = player->pos_x + player->dir_x * move_speed;
		new_y = player->pos_y + player->dir_y * move_speed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
	if (config->keys[MLX_KEY_S])
	{
		new_x = player->pos_x - player->dir_x * move_speed;
		new_y = player->pos_y - player->dir_y * move_speed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
}

void	move_strafe(t_config *config, double move_speed)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &config->data->player;
	if (config->keys[MLX_KEY_A])
	{
		new_x = player->pos_x - player->plane_x * move_speed;
		new_y = player->pos_y - player->plane_y * move_speed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
	if (config->keys[MLX_KEY_D])
	{
		new_x = player->pos_x + player->plane_x * move_speed;
		new_y = player->pos_y + player->plane_y * move_speed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
		{
			player->pos_x = new_x;
			player->pos_y = new_y;
		}
	}
}
