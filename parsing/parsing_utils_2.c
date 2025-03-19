/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:41:29 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 17:16:22 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	pars_position(char *line, t_config *config)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (config->north.path != NULL)
			return (printf("Error\nDuplicat textures: %s", line), -1);
		return (parse_texture(line + 3, &config->north));
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (config->south.path != NULL)
			return (printf("Error\nDuplicat textures: %s", line), -1);
		return (parse_texture(line + 3, &config->south));
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (config->west.path != NULL)
			return (printf("Error\nDuplicat textures: %s", line), -1);
		return (parse_texture(line + 3, &config->west));
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (config->east.path != NULL)
			return (printf("Error\nDuplicat textures: %s", line), -1);
		return (parse_texture(line + 3, &config->east));
	}
	return (printf("Error\nInvalid line: %s", line), -1);
}

void	flood_fill_mark(char **map, int x, int y, t_config *config)
{
	if (x < 0 || y < 0 || x >= config->map.width
		|| y >= config->map.height || map[y][x] != ' ')
		return ;
	map[y][x] = 'O';
	flood_fill_mark(map, x + 1, y, config);
	flood_fill_mark(map, x - 1, y, config);
	flood_fill_mark(map, x, y + 1, config);
	flood_fill_mark(map, x, y - 1, config);
}

void	mark_outer_spaces(char **map, t_config *config)
{
	int	x;
	int	y;

	x = 0;
	while (x < config->map.width)
	{
		if (map[0][x] == ' ')
			flood_fill_mark(map, x, 0, config);
		if (map[config->map.height - 1][x] == ' ')
			flood_fill_mark(map, x, config->map.height - 1, config);
		x++;
	}
	y = 0;
	while (y < config->map.height)
	{
		if (map[y][0] == ' ')
			flood_fill_mark(map, 0, y, config);
		if (map[y][config->map.width - 1] == ' ')
			flood_fill_mark(map, config->map.width - 1, y, config);
		y++;
	}
}

int	flood_fill(char **map, int x, int y, t_config *config)
{
	if (x < 0 || y < 0 || x >= config->map.width || y >= config->map.height)
		return (0);
	if (map[y][x] == 'O')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == 'V' || map[y][x] == '1')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y, config))
		return (0);
	if (!flood_fill(map, x - 1, y, config))
		return (0);
	if (!flood_fill(map, x, y + 1, config))
		return (0);
	if (!flood_fill(map, x, y - 1, config))
		return (0);
	return (1);
}

int	find_player(t_config *config, int j, int i, char c)
{
	config->map.player_x = j;
	config->map.player_y = i;
	config->map.player_dir = c;
	return (1);
}
