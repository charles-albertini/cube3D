/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:18 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	unsigned int	size;
	char			*out;
	size_t			i;

	i = 0;
	size = ft_strlen ((char *)str);
	if (start > size || !size)
		return (ft_strdup(""));
	if (start + len > size)
		len = size - start;
	out = malloc(sizeof(char) * (len + 1));
	if (out == NULL)
		return (NULL);
	while (len > 0)
	{
		out[i] = str[start];
		i ++;
		start ++;
		len --;
	}
	out[i] = '\0';
	return (out);
}
/*
#include <stdio.h>
#include <string.h>

int    main(int argc, char **argv)
{
	char *str;
	if (argc == 4)
	{
	    str = ft_substr(argv[1], atoi(argv[2]), atoi(argv[3]));
	    printf("%s\n", str);
	    free(str);
	}
}
*/
