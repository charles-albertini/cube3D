/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:34:00 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*new;
	int		i;
	int		len;

	if (!lst || !f || !del)
	{
		return (NULL);
	}
	i = 0;
	len = ft_lstsize(lst);
	newlist = NULL;
	while (i < len)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
			(*del)(lst);
		ft_lstadd_back(&newlist, new);
		lst = lst->next;
		i++;
	}
	return (newlist);
}
/*
#include <stdio.h>

void ft_del(void *lst) // PAS DEMANDE del un lst
{
	t_list *supp = (t_list *)lst;
    if (lst == NULL)
        return;
    supp->content = NULL;
}

void *double_value(void *content) // PAS DEMANDE pour tester la fonction lstmap
{
    if (content == NULL)
        return NULL;

    // Alloue un nouvel entier
    int *new_value = malloc(sizeof(int));
    if (new_value == NULL)
        return NULL;

    // Double la valeur pointée par content
    *new_value = (*(int *)content) * 2;
    return new_value;
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

	printf("liste:\n");
	aff_lst(first);

	size = ft_lstsize(first);
	printf("\nsize: \n%d\n", size);

	printf("\nlast list:\n");
	aff_lst(ft_lstlast(first));

	//ft_lstclear(&first, *ft_del);
	//aff_lst(first);

	//ft_lstiter(first, *ft_addone);
	//printf("\niteration:\n");
	//aff_lst(first);

	t_list *testmap = ft_lstmap(first, double_value, ft_del);
	printf("\nmap:\n");
	aff_lst(testmap);





	return (0);
}
*/
