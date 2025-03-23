/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:02:41 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/23 13:09:16 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_cast_rays(t_config *config)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		config->data->ray.camera_x = 2 * x / (double)WIN_WIDTH -1;
		config->data->ray.dir_x = config->data->player.dir_x
			+ config->data->player.plane_x * config->data->ray.camera_x;
		config->data->ray.dir_y = config->data->player.dir_y
			+ config->data->player.plane_y * config->data->ray.camera_x;
		ft_calc_delta_dist(config);
		ft_calc_step_and_side_dist(config);
		perf_dda(config);
		calc_wall_height(config);
		x++;
	}
}

void	calc_wall_height(t_config *config)
{
	if (config->data->ray.side == 0)
		config->data->ray.wall_dist = (config->data->ray.map_x
				- config->data->player.pos_x
				+ (1 - config->data->ray.step_x) / 2) / config->data->ray.dir_x;
	else
		config->data->ray.wall_dist = (config->data->ray.map_y
				- config->data->player.pos_y
				+ (1 - config->data->ray.step_y) / 2) / config->data->ray.dir_y;
	config->data->ray.line_height = (int)(WIN_HEIGHT
			/ config->data->ray.wall_dist);
	config->data->ray.draw_start = -config->data->ray.line_height
		/ 2 + WIN_HEIGHT / 2;
	config->data->ray.draw_end = config->data->ray.line_height
		/ 2 + WIN_HEIGHT / 2;
	if (config->data->ray.draw_start < 0)
		config->data->ray.draw_start = 0;
	if (config->data->ray.draw_end >= WIN_HEIGHT)
		config->data->ray.draw_end = WIN_HEIGHT - 1;
	if (config->data->ray.side == 0)
		config->data->ray.wall_x = config->data->player.pos_y
			+ config->data->ray.wall_dist * config->data->ray.dir_y;
	else
		config->data->ray.wall_x = config->data->player.pos_x
			+ config->data->ray.wall_dist * config->data->ray.dir_x;
	config->data->ray.wall_x -= floor(config->data->ray.wall_x);
}
