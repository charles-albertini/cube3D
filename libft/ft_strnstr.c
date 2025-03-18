/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:37:56 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <bsd/string.h>

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (find[j] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		if (str[i] == find[j])
		{
			k = i;
			while (str[k] == find[j] && k < len)
			{
				j ++;
				k ++;
				if (find[j] == '\0' )
					return ((char *)&str[i]);
			}
		}
		j = 0;
		i ++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>

int    main(int argc, char **argv)
{
    if (argc == 4)
    {
        char *result = strnstr(argv[1], argv[2], atoi(argv[3]));
        char *result2 = ft_strnstr(argv[1], argv[2], atoi(argv[3]));
        printf("real : %s\n", result);
        printf("mine : %s\n", result2);
    }
    return (0);
}
*/
/*
cherche une osus chaine dans une chaine
retourn un pointeur vers la premieree occuence trouve
compiler avec -lbsd
*/
