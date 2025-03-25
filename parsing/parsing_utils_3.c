/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:44:55 by calberti          #+#    #+#             */
/*   Updated: 2025/03/25 11:04:42 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	add_tab(t_config *config, int i, int j)
{
	if (config->map.grid[i][j] == '\t')
		return (1);
	return (0);
}

char	**make_normalize(t_config *config, char **normalize, int i, int j)
{
	int	len;
	int	tab;

	while (i < config->map.height)
	{
		tab = 0;
		j = 0;
		len = ft_strlen_width(config->map.grid[i]);
		normalize[i] = malloc(config->map.width + 2);
		while (j < len -1)
		{
			tab += add_tab(config, i, j);
			normalize[i][j] = config->map.grid[i][j];
			j++;
		}
		while (j < config->map.width -1 - (tab * 4))
		{
			normalize[i][j] = ' ';
			j++;
		}
		normalize[i][j] = '\n';
		normalize[i][j + 1] = '\0';
		i++;
	}
	return (normalize);
}

char	*ft_strdup_tab_to_space(char *src)
{
	int		i;
	int		j;
	int		len;
	char	*cpy;
	int		space_count;

	len = ft_strlen_width(src);
	cpy = malloc(len + 1);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\t')
		{
			space_count = 4 - (j % 4);
			while (space_count--)
				cpy[j++] = ' ';
		}
		else
			cpy[j++] = src[i];
		i++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*supp_zero(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0 && str[len] != '1')
	{
		if (str[len] == '0')
		{
			str[len] = ' ';
			len --;
		}
		else
			len --;
	}
	return (str);
}

int	update_player_xy(int player, int dir)
{
	if (dir > player)
		return (1);
	else
		return (-1);
}
