/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:11:35 by calberti          #+#    #+#             */
/*   Updated: 2025/03/22 16:44:42 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	handle_forward_backward(t_config *config, double moveSpeed)
{
	t_player	*player;

	player = &config->data->player;
	if (config->keys[MLX_KEY_W])
	{
		double new_x = player->pos_x + player->dir_x * moveSpeed;
		double new_y = player->pos_y + player->dir_y * moveSpeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
			(player->pos_x = new_x, player->pos_y = new_y);
	}
	if (config->keys[MLX_KEY_S])
	{
		double new_x = player->pos_x - player->dir_x * moveSpeed;
		double new_y = player->pos_y - player->dir_y * moveSpeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
			(player->pos_x = new_x, player->pos_y = new_y);
	}
}

static void handle_strafe(t_config *config, double moveSpeed)
{
	t_player *player = &config->data->player;

	if (config->keys[MLX_KEY_A])
	{
		double new_x = player->pos_x - player->plane_x * moveSpeed;
		double new_y = player->pos_y - player->plane_y * moveSpeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
			(player->pos_x = new_x, player->pos_y = new_y);
	}
	if (config->keys[MLX_KEY_D])
	{
		double new_x = player->pos_x + player->plane_x * moveSpeed;
		double new_y = player->pos_y + player->plane_y * moveSpeed;
		if (config->map.grid[(int)new_y][(int)new_x] != '1')
			(player->pos_x = new_x, player->pos_y = new_y);
	}
}

void handle_movement(t_config *config)
{
	double moveSpeed = 0.05;

	handle_forward_backward(config, moveSpeed);

	handle_strafe(config, moveSpeed);
}

void continuous_render(void *param)
{
	t_config *config = (t_config *)param;

	// Gérer les mouvements
	handle_movement(config);

	// Gérer la rotation
	handle_rotation(config);

	// Redessiner la scène ou mettre à jour l'affichage
	render_frame(config);
}