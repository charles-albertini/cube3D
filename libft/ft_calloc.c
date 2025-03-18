/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:24:48 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size != 0 && nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}
	tab = malloc(size * nmemb);
	if (tab == NULL)
	{
		return (NULL);
	}
	ft_bzero(tab, nmemb * size);
	return (tab);
}
/*
#include <stdio.h>

int    main(void)
{
    int    *tab;
    tab = ft_calloc(5, sizeof(int));
    
	int i = 0;
	while (i < 5)
	{
		printf("%d \n", tab[i]);
		i++;
	}
	free(tab);	 
}
*/
/*
a l'inverse de malloc, calloc initialise la memoire a 0
*/
