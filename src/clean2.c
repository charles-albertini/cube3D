/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:37:13 by calberti          #+#    #+#             */
/*   Updated: 2025/03/24 15:51:07 by calberti         ###   ########.fr       */
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

void	free_images(t_config *conf)
{
	if (conf->imag)
	{
		free(conf->imag);
		conf->imag = NULL;
	}
}

void	cleanup(t_config *conf)
{
	if (conf->imag)
	{
		mlx_delete_image(conf->mlx, conf->imag->north);
		mlx_delete_image(conf->mlx, conf->imag->south);
		mlx_delete_image(conf->mlx, conf->imag->west);
		mlx_delete_image(conf->mlx, conf->imag->east);
		free_images(conf);
	}
	if (conf->textu)
		free_textures(conf);
}