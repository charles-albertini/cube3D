/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:36:50 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	nbr;

	nbr = 0;
	while (src[nbr])
	{
		dest [nbr] = src [nbr];
		nbr ++;
	}
	dest [nbr] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*cpy;

	cpy = malloc(ft_strlen(src) + 1);
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strcpy(cpy, src);
	return (cpy);
}

/*
#include <stdio.h>
#include <string.h>
int	main (void)
{
	char	*str = "phrase a copier";
	char	*strcpy;
	char	*strcpy2;

	strcpy = ft_strdup(str);
	strcpy2 = strdup(str);
	printf("%s \n", strcpy);
	printf("%s \n", strcpy2);
	free(strcpy);
	free(strcpy2);
}
*/
/*
strdup c'est un strcpy mais qui alloue de la memoire
*/