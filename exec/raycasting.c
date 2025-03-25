/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:41:13 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/25 11:20:30 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_calc_delta_dist(t_config *config)
{
	config->data->ray.map_x = (int)config->data->player.pos_x;
	config->data->ray.map_y = (int)config->data->player.pos_y;
	config->data->ray.deltadist_x = fabs(1 / config->data->ray.dir_x);
	config->data->ray.deltadist_y = fabs(1 / config->data->ray.dir_y);
}

void	ft_calc_step_and_side_dist(t_config *config)
{
	if (config->data->ray.dir_x < 0)
	{
		config->data->ray.step_x = -1;
		config->data->ray.sidedist_x = (config->data->player.pos_x
				- config->data->ray.map_x) * config->data->ray.deltadist_x;
	}
	else
	{
		config->data->ray.step_x = 1;
		config->data->ray.sidedist_x = (config->data->ray.map_x + 1.0
				- config->data->player.pos_x) * config->data->ray.deltadist_x;
	}
	if (config->data->ray.dir_y < 0)
	{
		config->data->ray.step_y = -1;
		config->data->ray.sidedist_y = (config->data->player.pos_y
				- config->data->ray.map_y) * config->data->ray.deltadist_y;
	}
	else
	{
		config->data->ray.step_y = 1;
		config->data->ray.sidedist_y = (config->data->ray.map_y + 1.0
				- config->data->player.pos_y) * config->data->ray.deltadist_y;
	}
}

void	update_ray_position(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

int	check_hit(t_ray *ray, char **map, int map_width, int map_height)
{
	if (ray->map_y < 0 || ray->map_y >= map_height
		|| ray->map_x < 0 || ray->map_x >= map_width)
	{
		return (1);
	}
	if (map && ray->map_y >= 0 && ray->map_y < map_height
		&& ray->map_x >= 0 && ray->map_x < map_width
		&& (map[ray->map_y][ray->map_x] == '1'
		|| map[ray->map_y][ray->map_x] == 'O'))
	{
		return (1);
	}
	return (0);
}

void	perf_dda(t_config *config)
{
	int		hit;
	t_ray	*ray;
	char	**map;
	int		map_height;
	int		map_width;

	hit = 0;
	ray = &config->data->ray;
	map = config->data->map;
	map_height = config->map.height;
	map_width = config->map.width;
	while (!hit)
	{
		update_ray_position(ray);
		hit = check_hit(ray, map, map_width, map_height);
	}
}
