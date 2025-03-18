/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:11 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_char_is(char const c, char const *find)
{
	int	i;

	i = 0;
	while (find[i])
	{
		if (find[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

int	ft_count_befor(char const *s1, char const *set)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (ft_char_is(s1[i], set) == 1)
	{
		i++;
		nb++;
	}
	return (nb);
}

int	ft_count_after(char *s1, char const *set)
{
	int	j;
	int	nb;

	nb = 0;
	j = ft_strlen(s1) - 1;
	while (ft_char_is(s1[j], set) == 1)
	{
		j--;
		nb++;
	}
	return (nb);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*out;
	int		i;
	int		j;
	int		k;
	int		len;

	i = ft_count_befor(s1, set);
	j = ft_count_after(s1, set);
	k = 0;
	len = ft_strlen(s1);
	if (len - (i + j) < 0)
		out = malloc (sizeof(char) * 1);
	else
		out = malloc (sizeof(char) * (len - (i + j) + 1));
	if (out == NULL)
		return (NULL);
	while (i < len - j)
	{
		out[k] = s1[i];
		k ++;
		i ++;
	}
	out[k] = '\0';
	return (out);
}
/*
 #include <string.h>
 #include <stdio.h>
 
 int    main(int argc, char **argv)
 {
	char *str;
	(void)argv;
	if (argc == 1)
 	{
		str = ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t");
 		printf("%s\n", str);
		free(str);
 	}
 }
 */
