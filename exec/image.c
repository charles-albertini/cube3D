/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:05:48 by calberti          #+#    #+#             */
/*   Updated: 2025/03/20 16:43:43 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_textures(t_config *config)
{
	config->textu = malloc(sizeof(t_textures));
	config->textu->north = mlx_load_png("textures/north.png");
	config->textu->south = mlx_load_png("textures/south.png");
	config->textu->west = mlx_load_png("textures/west.png");
	config->textu->east = mlx_load_png("textures/east.png");
}

void	get_images(t_config *conf)
{
	conf->imag = malloc(sizeof(t_images));
	conf->imag->north = mlx_texture_to_image(conf->mlx, conf->textu->north);
	conf->imag->south = mlx_texture_to_image(conf->mlx, conf->textu->south);
	conf->imag->west = mlx_texture_to_image(conf->mlx, conf->textu->west);
	conf->imag->east = mlx_texture_to_image(conf->mlx, conf->textu->east);
	mlx_delete_texture(conf->textu->north);
	mlx_delete_texture(conf->textu->south);
	mlx_delete_texture(conf->textu->west);
	mlx_delete_texture(conf->textu->east);
}

void	draw_map(t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (config->map.grid[y])
	{
		x = 0;
		printf("non\n");
		while (config->map.grid[y][x])
		{
			while (config->map.grid[y][x] == ' ')
				x++;
			mlx_image_to_window(config->mlx, config->imag->north, x * 32, y * 32);
			if (config->map.grid[y][x] == '1')
				mlx_image_to_window(config->mlx, config->imag->south, x * 32, y * 32);
			if (config->map.grid[y][x] == 'N')
				mlx_image_to_window(config->mlx, config->imag->east, x * 32, y * 32);
			x++;
		}
		y++;
	}
}


