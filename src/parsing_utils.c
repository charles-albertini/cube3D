/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:09:40 by calberti          #+#    #+#             */
/*   Updated: 2025/03/18 15:43:18 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


int is_empty_line(char *line)
{
	int i;
	int num;

	num = 0;
	i=0;
	if(line)
	{
		if (line[i] == '\n')
			return(1);

    	while (line[i])
    	{
        	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            	return (0);
        	i++;
    	}
    	return (1);
	}
	return(0);
}

int ft_arrlen(char **arr)
{
    int i = 0;
    
    while (arr[i])
        i++;
    return (i);
}

void free_array(char **arr)
{
    int i = 0;
    
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int is_all_num(char *str)
{
	int	i;
	int len;
	int verif;

	i = 0;
	verif = 0;
	len = ft_strlen(str);
	if (str[len -1] == '\n')
		len --;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		return(1);
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		verif = 1;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i != len || verif == 0)	
		return(1);
	return(0);	
}

char *trim_left(char *str)
{
    while (*str == ' ' || *str == '\t')  // Enlève les espaces/tabs du début
        str++;
    return (str);
}




