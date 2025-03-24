/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:10:43 by calberti          #+#    #+#             */
/*   Updated: 2025/03/24 15:19:50 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	set_player_plane(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (dir == 'W')
	{
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}

static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (dir == 'W')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	set_player_plane(player, dir);
}

void	init_player_from_config(t_config *config)
{
	t_player	*player;

	player = &config->data->player;
	player->pos_x = config->map.player_x + 0.5;
	player->pos_y = config->map.player_y + 0.5;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	set_player_direction(player, config->map.player_dir);
}
