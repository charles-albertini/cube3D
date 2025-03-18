/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:02 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *)s;
	if (c == '\0')
	{
		i = ft_strlen((char *)s);
		return ((char *)&str[i]);
	}
	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	char	*i;
	char	*j;

	if (argc == 3)
	{
		i = ft_strrchr(argv[1], atoi (argv[2]));
		j = strrchr(argv[1], atoi (argv[2]));
		printf("Mine : %s\nReal : %s\n", i, j);
	}
	return (0);
}
*/
/*
meme chose que strchrmais on cherches le dernier occurence 
donc on part de la fin
*/
