/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:34:31 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		if (s2[i] == (unsigned char)c)
		{
			return (&s2[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int    main(int argc, char **argv)
{
    char    *i;
    char    *j;

    if (argc == 4)
    {
        i = ft_memchr(argv[1], atoi(argv[2]), atoi(argv[3]));
        j = memchr(argv[1], atoi(argv[2]), atoi(argv[3]));
        printf("Mine : %s\nReal : %s\n", i, j);
		// on cast en unsigned char pcq ca correspond a 1 octet
    }
    return (0);
}
*/
/*
meme chose que strchr mais avec n'importe quoi 
et on cherche dans une taille definie
*/
