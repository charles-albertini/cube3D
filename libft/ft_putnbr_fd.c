/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:36:04 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}
/*
#include <fcntl.h>

int	main(int argc, char **argv)
{
    int fd = open ("test.txt", O_WRONLY | O_CREAT, 0644);
	if (argc == 2)
	{
		ft_putnbr_fd(atoi(argv[1]), fd);
	}
	return (0);
}
*/
