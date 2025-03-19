/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:01:17 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 19:35:40 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	parse_file(char *filename, t_config *config)
{
	int		fd;
	char	*line;
	int		empty;

	empty = 0;
	init_config(config);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nNo such file or directory\n"), 0);
	line = get_next_line(fd);
	while (line)
	{
		empty = 1;
		if (config->map.grid != NULL && is_empty_line(line))
			return (printf("Error\nMap end\n"), close(fd), clean_line(line), 0);
		if (!parse_line(line, config))
			return (close(fd), clean_line(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (empty == 0)
		return (printf("Error\nEmpty file\n"), 0);
	return (validate_config(config));
}

int	parse_line(char *line, t_config *config)
{
	int	pars_pos;

	if (is_empty_line(line))
		return (1);
	if (config->map.grid != NULL)
		return (parse_map_line(line, config));
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (config->floor.value != -1)
			return (printf("Error\nDuplicat colors"), 0);
		return (parse_color(line + 2, &config->floor));
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (config->ceiling.value != -1)
			return (printf("Error\nDuplicat colors"), 0);
		return (parse_color(line + 2, &config->ceiling));
	}
	else if (is_map_line(line))
		return (start_map_parsing(line, config));
	pars_pos = pars_position(line, config);
	if (pars_pos == -1)
		return (0);
	else
		return (pars_pos);
}

int	parse_texture(char *path, t_texture *texture)
{
	int	len;

	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\n'
			|| path[len - 1] == '\t'))
		path[--len] = '\0';
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".png") != 0)
		return (printf("Error\nInvalid file extension: %s", path), 0);
	while (*path == ' ')
		path++;
	if (*path == '\0')
		return (printf("Error\nEmpty texture path"), 0);
	texture->path = ft_strdup(path);
	if (texture->path == NULL)
		return (printf("Error\nMemory allocation failed"), 0);
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	while (*str == ' ')
		str++;
	parts = ft_split(str, ',');
	if (parts == NULL)
		return (0);
	if (ft_arrlen(parts) != 3)
		return (printf("Error\nColor format: %s", str), free_array(parts), 0);
	if (is_all_num(parts[0]) || is_all_num(parts[1]) || is_all_num(parts[2]))
		return (printf("Error\nWrong values\n"), free_array(parts), 0);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("Error\nColor between 0-255\n"), free_array(parts), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	color->value = (r << 16) | (g << 8) | b;
	free_array(parts);
	return (1);
}

int	parse_cub_file(char *filename, t_config *config)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error\nInvalid file extension: %s\n", filename);
		return (0);
	}
	if (!parse_file(filename, config))
	{
		clean_config(config);
		return (0);
	}
	return (1);
}
