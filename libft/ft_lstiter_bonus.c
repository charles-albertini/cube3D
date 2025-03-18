/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:44 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

/*
#include <stdio.h>

void ft_addone (void *nb) // PAS DEMANDE test la fonction lstiter
{
    int *new = (int*)nb;
    (*new) ++;

}

void aff_lst(t_list *lst) // PAS DEMANDE affiche list
{
	if (lst == NULL)
	{
		printf("empty list\n");
		return;
	}
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
	int nb3 = 11;
	int size;

	t_list *first = ft_lstnew(&nb);
	t_list *new = ft_lstnew(&nb2);
	t_list *new2 = ft_lstnew(&nb3);

	ft_lstadd_front(&first, new);
	ft_lstadd_back(&first, new2);

	printf("liste :\n");
	aff_lst(first);

	size = ft_lstsize(first);
	printf("size : %d\n", size);

	printf("last list :");
	aff_lst(ft_lstlast(first));

	//ft_lstclear(&first, *ft_del);
	//aff_lst(first);

	ft_lstiter(first, *ft_addone);
	aff_lst(first);

	return (0);
}
*/
