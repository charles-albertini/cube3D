/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:37:10 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size <= len_dest)
		return (size + len_src);
	while (src[i] != '\0' && i < (size - len_dest - 1))
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_dest + len_src);
}
/*
#include <string.h>
#include <stdio.h>
 
int main (void)
{
char  dest[10] = "salut";
const char *src = "comment";
unsigned int i = 10;
 
printf("%zu \n", ft_strlcat(dest, src, i));
printf("%s \n", dest);
//n = size de dest - len de dest - 1 = 12 - 5 - 1 = 6
}
*/
/*
on colle les deux chaine mais y a une securite avec size
qui evite les debordement de tampon 
ca renvoie la taille total de ce que ca essayer de creer
*/
