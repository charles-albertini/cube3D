/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:03:43 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 19:35:50 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	validate_map(t_config *config)
{
	if (!find_player_position(config))
		return (0);
	if (!normalize_map(config))
		return (0);
	if (!check_map_borders(config))
		return (0);
	return (1);
}

int	find_player_position(t_config *config)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	player_count = 0;
	i = 0;
	j = 0;
	while (i < config->map.height)
	{
		j = 0;
		while (config->map.grid[i][j] != '\0')
		{
			c = config->map.grid[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count += find_player(config, j, i, c);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (printf("Error\nNo player position found"), 0);
	if (player_count > 1)
		return (printf("Error\nMultiple player position found"), 0);
	return (1);
}

int	normalize_map(t_config *config)
{
	int		i;
	int		j;
	char	**normalize;

	i = 0;
	j = 0;
	normalize = malloc(sizeof(char *) * config->map.height);
	if (!normalize)
		return (0);
	normalize = make_normalize(config, normalize, i, j);
	i = 0;
	while (i < config->map.height)
	{
		free(config->map.grid[i]);
		i++;
	}
	free(config->map.grid);
	config->map.grid = normalize;
	return (1);
}

int	check_map_borders(t_config *config)
{
	char	**copy;
	int		i;
	int		res;

	copy = malloc(sizeof(char *) * config->map.height);
	i = 0;
	while (i < config->map.height)
	{
		copy[i] = ft_strdup(config->map.grid[i]);
		if (!clean_copy(copy, i))
			return (0);
		i++;
	}
	mark_outer_spaces(copy, config);
	res = flood_fill(copy, config->map.player_x, config->map.player_y, config);
	i = 0;
	while (i < config->map.height)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
	if (!res)
		printf("Error\nMap is not properly closed\n");
	return (res);
}
