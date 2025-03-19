/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:04:49 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 16:59:38 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	clean_config(t_config *config)
{
	int	i;

	i = 0;
	if (config->north.path)
		free(config->north.path);
	if (config->south.path)
		free(config->south.path);
	if (config->west.path)
		free(config->west.path);
	if (config->east.path)
		free(config->east.path);
	if (config->map.grid)
	{
		while (i < config->map.height)
		{
			free(config->map.grid[i]);
			i ++;
		}
		free(config->map.grid);
	}
}

void	clean_line(char *line)
{
	if (line)
		free(line);
}

int	clean_copy(char **copy, int i)
{
	if (!copy[i])
	{
		while (i > 0)
			free(copy[--i]);
		free(copy);
		return (0);
	}
	return (1);
}
