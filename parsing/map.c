/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:36:58 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 19:33:27 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != '\t' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	start_map_parsing(char *first_line, t_config *config)
{
	config->map.grid = malloc(sizeof(char *));
	if (config->map.grid == NULL)
		return (0);
	config->map.grid[0] = ft_strdup_tab_to_space(first_line);
	if (config->map.grid[0] == NULL)
	{
		free(config->map.grid);
		config->map.grid = NULL;
		return (0);
	}
	config->map.height = 1;
	config->map.width = ft_strlen_width(first_line);
	return (1);
}

int	verif_line(char *line)
{
	if (is_empty_line(line))
	{
		printf("Error\nEmpty line in map\n");
		return (0);
	}
	if (!is_map_line(line))
	{
		printf("Error\nInvalid character in map\n");
		return (0);
	}
	return (1);
}

int	parse_map_line(char *line, t_config *config)
{
	char	**new_grid;
	int		i;
	int		line_len;

	i = 0;
	if (!verif_line(line))
		return (0);
	new_grid = malloc(sizeof(char *) * (config->map.height + 1));
	if (new_grid == NULL)
		return (0);
	while (i < config->map.height)
	{
		new_grid[i] = config->map.grid[i];
		i++;
	}
	new_grid[config->map.height] = ft_strdup_tab_to_space(line);
	if (new_grid[config->map.height] == NULL)
		return (free(new_grid), 0);
	line_len = ft_strlen_width(line);
	if (line_len > config->map.width)
		config->map.width = line_len;
	free(config->map.grid);
	config->map.grid = new_grid;
	config->map.height++;
	return (1);
}

int	validate_config(t_config *config)
{
	if (config->north.path == NULL || config->south.path == NULL
		|| config->west.path == NULL || config->east.path == NULL)
	{
		printf("Error\nMissing texture(s)\n");
		return (0);
	}
	if (config->floor.value == -1 || config->ceiling.value == -1)
	{
		printf("Error\nMissing color(s)\n");
		return (0);
	}
	if (config->map.grid == NULL)
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	return (validate_map(config));
}
