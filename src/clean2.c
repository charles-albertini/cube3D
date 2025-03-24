/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:37:13 by calberti          #+#    #+#             */
/*   Updated: 2025/03/24 23:14:17 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_textures(t_config *conf)
{
	if (conf->textu)
	{
		free(conf->textu);
		conf->textu = NULL;
	}
}

void	del_text(t_config *config)
{
	mlx_delete_texture(config->textu->north);
	mlx_delete_texture(config->textu->south);
	mlx_delete_texture(config->textu->west);
	mlx_delete_texture(config->textu->east);
}

void	cleanup(t_config *conf)
{
	int	i;

	i = 0;
	del_text(conf);
	if (conf->textu)
		free_textures(conf);
	if (conf->data)
		free(conf->data);
	if (conf->map.grid)
	{
		while (i < conf->map.height)
		{
			free(conf->map.grid[i]);
			i++;
		}
		free(conf->map.grid);
	}
	if (conf->north.path)
		free(conf->north.path);
	if (conf->south.path)
		free(conf->south.path);
	if (conf->east.path)
		free(conf->east.path);
	if (conf->west.path)
		free(conf->west.path);
}
