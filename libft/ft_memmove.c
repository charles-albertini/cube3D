/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:35:14 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest1;
	unsigned char	*src1;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	if (dest > src)
	{
		while (n > 0)
		{
			dest1[n - 1] = src1[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest1);
}
/*
#include <string.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*i;
	char	*j;

	if (argc == 4)
	{
		i = ft_memmove(argv[1], argv[2], atoi(argv[3]));
		j = memmove(argv[1], argv[2], atoi(argv[3]));
		printf("Mine : %s\nReal : %s\n", i, j);
	}
	return (0);
}
*/

/*
 (dest > src)  ca signifie que la zone dest se trouve apres src
 dans la memoire et que ca peut donc creer un chevauchement
 l'adresse memoire du pointeur pointe vers le premier octet, 
 si dest > src on risque d'ecraser les donnee avant de les copier
 dest1[n - 1] = src1[n - 1] on commence donc a copier a partir de la fin
 pour etre sur
 */