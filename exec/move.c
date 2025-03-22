/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axburin- <axburin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:04:37 by calberti          #+#    #+#             */
/*   Updated: 2025/03/22 17:34:12 by axburin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_up(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32 - 1]
		[config->imag->east->instances->x / 32] != '1')
	{
		config->imag->east->instances->y -= 32;
	}
}

void	move_right(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32]
		[config->imag->east->instances->x / 32 + 1] != '1')
	{
		config->imag->east->instances->x += 32;
	}
}

void	move_down(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32 + 1]
		[config->imag->east->instances->x / 32] != '1')
	{
		config->imag->east->instances->y += 32;
	}
}

void	move_left(t_config *config)
{
	if (config->map.grid[config->imag->east->instances->y / 32]
		[config->imag->east->instances->x / 32 - 1] != '1')
	{
		config->imag->east->instances->x -= 32;
	}
}
