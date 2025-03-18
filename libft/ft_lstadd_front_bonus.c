/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:20 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:20 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/* on veut ajouter un element au debut de la list on dit donc que
 new -> next point vers le premier truc pour qu'il se mette avant
 et ensuite on dit que mnt le premiere element est new on a donc
 new en premier element qui point maintenent vers *lst qui est devenue
 le deuxieme element */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if ((lst == NULL) || (new == NULL))
	{
		return ;
	}
	new->next = *lst;
	*lst = new;
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
	int nb = 8;
	int nb2 = 9;
	t_list *first = ft_lstnew(&nb);
	t_list *new = ft_lstnew(&nb2);
	ft_lstadd_front(&first, new);
	aff_lst(first);



	return (0);
}
*/
