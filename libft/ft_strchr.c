/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:36:28 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*le caractère c est comparé avec les caractères de la chaîne. 
Lorsqu'un entier supérieur à 255 (comme 1024) est converti en unsigned char, 
il est modifié par rapport à la taille de 256 (car 1024 % 256 = 0). 
Cela signifie que c est effectivement traité comme '\0' (caractère nul).*/
char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	if (c % 256 == 0)
		c = '\0';
	str = (unsigned char *)s;
	if (c == '\0')
	{
		i = ft_strlen((char *)s);
		return ((char *)&str[i]);
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
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
		i = ft_strchr(argv[1], atoi (argv[2]));
		j = strchr(argv[1], atoi (argv[2]));
		printf("Mine : %s\nReal : %s\n", i, j);
	}
	return (0);
}
*/
