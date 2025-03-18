/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:35:55 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i ++;
	}
	write(fd, "\n", 1);
}

/*
#include <fcntl.h>

int	main(int argc, char **argv)
{
    int fd = open ("test.txt", O_WRONLY | O_CREAT, 0644);
	if (argc == 2)
	{
        ft_putendl_fd(argv[1], fd);
	}
	return (0);
}
//0644 lire/ecrire par le proprio et lire pour les autres
//0 entre standard
//1 sortie standard
//2 sortie d'erreur
//3, 4, 5... les fichier qui seront succesivement ouvert
*/
