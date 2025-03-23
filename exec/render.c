/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:11:22 by calberti          #+#    #+#             */
/*   Updated: 2025/03/23 13:17:31 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_wall_texture(t_config *config, mlx_texture_t **texture, int *tex_x)
{
	t_ray	*ray;
	double	wall_x;

	ray = &config->data->ray;
	if (ray->side == 0 && ray->dir_x > 0)
		*texture = config->textu->east;
	else if (ray->side == 0 && ray->dir_x <= 0)
		*texture = config->textu->west;
	else if (ray->side == 1 && ray->dir_y > 0)
		*texture = config->textu->south;
	else
		*texture = config->textu->north;
	wall_x = ray->wall_x;
	*tex_x = (int)(wall_x * (*texture)->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		*tex_x = (*texture)->width - *tex_x - 1;
}

void	draw_wall_texture(int x, t_config *config, mlx_image_t *img)
{
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	uint32_t		color;
	int				y;

	ray = &config->data->ray;
	get_wall_texture(config, &texture, &tex_x);
	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
		if (ray->side == 1)
			color = ((color >> 1) & 0x7F7F7F7F) | (color & 0xFF);
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_wall(int x, t_config *config, mlx_image_t *img)
{
	t_ray	*ray;
	int	y;

	ray = &config->data->ray;
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(img, x, y, config->ceiling.value);
		y++;
	}
	draw_wall_texture(x, config, img);
	y = ray->draw_end;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(img, x, y, config->floor.value);
		y++;
	}
}

static void	initialize_image(t_config *config)
{
    if (config->current_image)
    {
        mlx_delete_image(config->mlx, config->current_image);
        config->current_image = NULL; // Réinitialiser le pointeur
    }
    mlx_image_t *img = mlx_new_image(config->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!img)
        return;
    config->current_image = img;
    config->data->map = config->map.grid;
}

void	render_frame(t_config *config)
{
	int	x;

	initialize_image(config);
	if (!config->current_image)
		return;
	mlx_image_t *img = config->current_image;
	x = 0;
	while (x < WIN_WIDTH)
	{
		config->data->ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		config->data->ray.dir_x = config->data->player.dir_x
			+ config->data->player.plane_x * config->data->ray.camera_x;
		config->data->ray.dir_y = config->data->player.dir_y
			+ config->data->player.plane_y * config->data->ray.camera_x;
		config->data->ray.map_x = (int)config->data->player.pos_x;
		config->data->ray.map_y = (int)config->data->player.pos_y;
		config->data->ray.deltadist_x = fabs(1 / config->data->ray.dir_x);
		config->data->ray.deltadist_y = fabs(1 / config->data->ray.dir_y);
		ft_calc_step_and_side_dist(config);
		perf_dda(config);
		calc_wall_height(config);
		draw_wall(x, config, img);
		x++;
	}
	mlx_image_to_window(config->mlx, img, 0, 0);
}
