/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:06:04 by calberti          #+#    #+#             */
/*   Updated: 2025/03/18 21:36:32 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_pos = 0;
    static int bytes_read = 0;
    int line_pos;
    char *line;

    if(fd < 0 || BUFFER_SIZE < 1)
        return(NULL);
    line = malloc(10000);
    if(!line)
        return(NULL);
    line_pos = 0;
    while(1)
    {
        if(buffer_pos >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if(bytes_read <= 0)
                break;
        }
        while(buffer_pos < bytes_read)
        {
            line[line_pos++] = buffer[buffer_pos++];
            if(line[line_pos - 1] == '\n')
            {
                line[line_pos] = '\0';
                return(line);
            }
        }
    }
	
    if(line_pos > 0)
    {
        line[line_pos] = '\0';
        return(line);
    }
    free(line);
    return(NULL);
}

// #include <stdio.h>
// int main(int argc, char *argv[])
// {
//     int		fd;
//     char	*line;
//     int		nb;
//     int		nb_read;
//     if (argc == 2) 
//     {
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return 0;    
//     }
//     if (argc == 1)
// 		fd = 0;
//     nb = 0;
//     nb_read = 15;
//     while (nb < nb_read)
//     {
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	if (line == NULL)
// 	    break;
// 	nb++;
//     }

//     close(fd);

//     return 0;
// }
