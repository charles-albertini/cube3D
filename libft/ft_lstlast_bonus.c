/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:55 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize(lst);
	while (i < len - 1)
	{
		lst = lst -> next;
		i ++;
	}
	return (lst);
}
/*
#include <stdio.h>

void aff_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%d\n", *(int *)(lst -> content));
		lst = lst -> next;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int nb = 10;
	int nb2 = 9;
	int nb3 = 8;
	int size;
	t_list *first = ft_lstnew(&nb);
	t_list *new = ft_lstnew(&nb2);
	t_list *new2 = ft_lstnew(&nb3);
	ft_lstadd_front(&first, new);
	ft_lstadd_front(&first, new2);
	size = ft_lstsize(first);
	printf("liste :\n");
	aff_lst(first);
	printf("size : %d\n", size);
	printf("last list :");
	aff_lst(ft_lstlast(first));



	return (0);
}
*/
