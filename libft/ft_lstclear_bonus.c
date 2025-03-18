/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:29 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*supp;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		supp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = supp;
	}
	lst = NULL;
}
/*
#include <stdio.h>

void del(void *lst) // PAS DEMANDE del un lst
{
    t_list *supp = (t_list *)lst;
    if (lst == NULL)
        return;
    supp->content = NULL;
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

	ft_lstclear(&first, *del);
	aff_lst(first);

	return (0);
}
*/
