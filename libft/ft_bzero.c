/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:24:31 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	tab[5] = {'1', '2', '3', '4', '5'};
	char	tab2[5] = {'1', '2', '3', '4', '5'};
	int	i;

	i = 0;
	ft_bzero(tab, 5);
	bzero(tab2, 5);
	printf("Mine : ");
	while (i <= 4)
	{
		printf("%c", tab[i]);
		i++;
	}
	i = 0;
	printf("\nReal : ");
	while (i <= 4)
	{
		printf("%c", tab2[i]);
		i++;
	}
	printf("\n");
}
*/
