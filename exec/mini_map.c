/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:41:45 by calberti          #+#    #+#             */
/*   Updated: 2025/03/25 16:03:45 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	draw_back(t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (y < config->map.height * T_SIZE)
	{
		x = 0;
		while (x < config->map.width * T_SIZE)
		{
			mlx_put_pixel(config->current_image, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

static void	draw_wall_map(t_config *config, int map_x, int map_y)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (map_x + i >= 0 && map_x + i < config->map.width * T_SIZE
				&& map_y + j >= 0 && map_y + j < config->map.height * T_SIZE)
			{
				mlx_put_pixel(config->current_image,
					map_x + i, map_y + j, 0x000000);
			}
			j++;
		}
		i++;
	}
}

static void	draw_player(t_config *config)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = (int)(config->data->player.pos_x * T_SIZE);
	player_y = (int)(config->data->player.pos_y * T_SIZE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (player_x + i >= 0 && player_x + i < config->map.width * T_SIZE
				&& player_y + j >= 0
				&& player_y + j < config->map.height * T_SIZE)
			{
				mlx_put_pixel(config->current_image, player_x + i, player_y + j,
					0xFF0000);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_config *config)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	draw_back(config);
	y = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < config->map.width)
		{
			map_x = x * T_SIZE;
			map_y = y * T_SIZE;
			if (config->map.grid[y] && config->map.grid[y][x] == '1')
				draw_wall_map(config, map_x, map_y);
			x++;
		}
		y++;
	}
	draw_player(config);
	mlx_image_to_window(config->mlx, config->current_image, 10, 10);
}
