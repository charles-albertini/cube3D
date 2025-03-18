/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:06:32 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:36:13 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_str(char *s1, char *s2, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		free(s1);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	str = ft_str(s1, s2, str);
	return (str);
}

char	*ft_new_buffer(char **buffer, int i, int error)
{
	int		j;
	char	*new_buffer;

	j = 0;
	if (error == 1)
	{
		free(*buffer);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen(*buffer) - i + 1);
	if (!new_buffer)
		return (NULL);
	j = 0;
	while ((*buffer)[i])
	{
		new_buffer[j] = (*buffer)[i];
		i++;
		j++;
	}
	new_buffer[j] = '\0';
	free(*buffer);
	return (new_buffer);
}

char	*get_line_from_buffer(char **buffer)
{
	char	*line;
	int		i;
	int		j;
	int		error;

	i = 0;
	j = 0;
	error = 0;
	if (!(*buffer) || !(*buffer)[0])
		return (NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = malloc(i + 2);
	while (j < i)
	{
		line[j] = (*buffer)[j];
		j++;
	}
	if ((*buffer)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if ((ft_strlen(*buffer) - i) == 0)
		error = 1;
	*buffer = ft_new_buffer(buffer, i, error);
	return (line);
}
