/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:05:48 by calberti          #+#    #+#             */
/*   Updated: 2025/03/24 21:07:22 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_textures(t_config *config)
{
	config->textu = malloc(sizeof(t_textures));
	config->textu->north = mlx_load_png(config->north.path);
	config->textu->south = mlx_load_png(config->south.path);
	config->textu->west = mlx_load_png(config->west.path);
	config->textu->east = mlx_load_png(config->east.path);
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
	free(conf->textu);
}
