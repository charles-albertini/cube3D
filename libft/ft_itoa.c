/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:31:58 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_intlen(long int n)
{
	long int	nb;

	nb = 0;
	while (n > 0)
	{
		n = n / 10;
		nb ++;
	}
	return (nb);
}

char	*positiv(long int n)
{
	int		size;
	int		size_save;
	char	*out;

	size = ft_intlen(n);
	size_save = size;
	out = malloc (sizeof(char) * (size + 1));
	if (out == NULL)
		return (NULL);
	while (size > 0)
	{
		out [size - 1] = n % 10 + '0';
		n = n / 10;
		size --;
	}
	out [size_save] = '\0';
	return (out);
}

char	*negativ(long int n)
{
	int		size;
	int		size_save;
	char	*out;

	n *= -1;
	size = ft_intlen(n);
	size_save = size;
	out = malloc (sizeof(char) * (size + 2));
	if (out == NULL)
		return (NULL);
	out [0] = '-';
	while (size > 0)
	{
		out [size] = n % 10 + '0';
		n = n / 10;
		size --;
	}
	out [size_save + 1] = '\0';
	return (out);
}

char	*ft_itoa(int n)
{
	char		*out;
	long int	nb;

	nb = (long int)n;
	if (nb == 0)
	{
		out = malloc(sizeof(char) * 2);
		if (out == NULL)
			return (NULL);
		out[0] = '0';
		out[1] = '\0';
	}
	else if (n < 0)
	{
		out = negativ(nb);
	}
	else
	{
		out = positiv(nb);
	}
	return (out);
}
/*
#include <string.h>
#include <stdio.h>

int    main(int argc, char **argv)
{
    char *str;
    	
    str = ft_itoa(atoi(argv[1]));
	if (argc == 2)
	{
		printf("%s\n", str);
		free(str);
	}
		
	
    return (0);
}
*/
