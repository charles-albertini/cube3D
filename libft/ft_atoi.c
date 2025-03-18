/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:17:04 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_atoi(const char *str)
{
	int	nbr;
	int	neg;
	int	out;

	nbr = 0;
	neg = 1;
	out = 0;
	while (str[nbr] == ' ' || str[nbr] == '\f' || str[nbr] == '\n'
		|| str[nbr] == '\r' || str[nbr] == '\t' || str[nbr] == '\v')
	{
		nbr ++;
	}
	if (str[nbr] == '+' || str[nbr] == '-')
	{
		if (str[nbr] == '-')
			neg = neg * (-1);
		nbr ++;
	}
	while (str[nbr] >= '0' && str[nbr] <= '9')
	{
		out = out * 10;
		out = out + str[nbr] - '0';
		nbr ++;
	}
	return (neg * out);
}
/*
#include <stdio.h>
 
int main (void)
{	
	printf("%d \n", ft_atoi("\n\n-713565465"));
	printf("%d \n", atoi("\n\n-713565465"));
}
*/