/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:38 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
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

t_list *ft_getlst(t_list *lst, int index) // PAS DEMANDE donne lst index
{
    int i = 0;

    while (lst != NULL)
    {
        if (i == index)
            return lst;
        lst = lst->next;
        i++;
    }
    return NULL;  // Si l'indice est hors de la portée de la liste
}

void aff_lst(t_list *lst) // PAS DEMANDE affiche list
{
	while (lst != NULL)
	{
		if (lst -> content != NULL)
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

	ft_lstdelone(ft_getlst(first, 1), del);
	aff_lst(first);
	

	
	return (0);
}
*/
