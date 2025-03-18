/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:37:49 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			nbr;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	nbr = 0;
	while ((s3[nbr] || s4[nbr]) && nbr < n)
	{
		if (s3[nbr] < s4[nbr])
			return (s3[nbr] - s4[nbr]);
		if (s3[nbr] > s4[nbr])
			return (s3[nbr] - s4[nbr]);
		nbr ++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
	size_t n = 6;
	if (argc == 3)
	{
	printf("%d\n", ft_strncmp("test\200", "test\0", n));
	printf("%d\n", strncmp(argv[1], argv[2], n));

	}
}
*/