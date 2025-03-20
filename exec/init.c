/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:34:34 by axburin-          #+#    #+#             */
/*   Updated: 2025/03/20 23:18:06 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_config(t_config *config)
{
	config->north.path = NULL;
	config->north.img = NULL;
	config->south.path = NULL;
	config->south.img = NULL;
	config->west.path = NULL;
	config->west.img = NULL;
	config->east.path = NULL;
	config->east.img = NULL;
	config->floor.value = -1;
	config->ceiling.value = -1;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->map.player_x = -1;
	config->map.player_y = -1;
	config->map.player_dir = '\0';
	config->data = NULL;
}

void	init_ray(t_config *config)
{
	config->data->ray.camera_x = 0;
	config->data->ray.dir_x = 0;
	config->data->ray.dir_y = 0;
	config->data->ray.map_x = 0;
	config->data->ray.map_y = 0;
	config->data->ray.step_x = 0;
	config->data->ray.step_y = 0;
	config->data->ray.sidedist_x = 0;
	config->data->ray.sidedist_y = 0;
	config->data->ray.deltadist_x = 0;
	config->data->ray.deltadist_y = 0;
	config->data->ray.wall_dist = 0;
	config->data->ray.wall_x = 0;
	config->data->ray.side = 0;
	config->data->ray.line_height = 0;
	config->data->ray.draw_start = 0;
	config->data->ray.draw_end = 0;
}

void	init_player(t_config *config)
{
	config->data->player.dir = '\0';
	config->data->player.pos_x = 0.0;
	config->data->player.pos_y = 0.0;
	config->data->player.dir_x = 0.0;
	config->data->player.dir_y = 0.0;
	config->data->player.plane_x = 0.0;
	config->data->player.plane_y = 0.0;
	config->data->player.has_moved = 0;
	config->data->player.move_x = 0;
	config->data->player.move_y = 0;
	config->data->player.rotate = 0;
}
void	init_map(t_config *config)
{
	config->data->mapinf.fd = 0;
	config->data->mapinf.line_count = 0;
	config->data->mapinf.path = NULL;
	config->data->mapinf.file = NULL;
	config->data->mapinf.height = 0;
	config->data->mapinf.width = 0;
	config->data->mapinf.index_end_of_map = 0;
}

void	init_data(t_config *config)
{
	if(!config->data)
		config->data = malloc(sizeof(t_data));
	config->data->mlx = NULL;
	config->data->win = NULL;
	config->data->win_height = WIN_HEIGHT;
	config->data->win_width = WIN_WIDTH;
	init_player(config);
	// init_texture(&data->texinfo);
	config->data->map = NULL;
	init_map(config);
	config->data->texture_pixels = NULL;
	config->data->textures = NULL;
}
void init_all(t_config *config )
{
	init_data(config);
	init_ray(config);
	// init_player(config);
	// init_map(config);
}
void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

