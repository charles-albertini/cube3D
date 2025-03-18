/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:06:04 by calberti          #+#    #+#             */
/*   Updated: 2025/03/14 19:36:15 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*malloc_temp(int fd)
{
	char	*temp_2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp_2 = malloc (BUFFER_SIZE + 1);
	if (temp_2 == NULL)
		return (NULL);
	return (temp_2);
}

void	*error_read(int bytes_read, char *temp, char **buffer)
{
	if (bytes_read < 0)
	{
		free(temp);
		if (buffer != NULL && *buffer != NULL)
			*buffer[0] = '\0';
		return (NULL);
	}
	return (buffer);
}

void	*error_line(char *line, char **buffer)
{
	if (!line)
	{
		if (buffer != NULL && *buffer != NULL)
			free(*buffer);
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*temp;
	char		*line;
	int			bytes_read;

	temp = malloc_temp(fd);
	while (1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (error_read(bytes_read, temp, &buffer) == 0)
			return (NULL);
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, temp);
		if (buffer == NULL)
			break ;
		if (ft_strchr_gnl(buffer, '\n') || bytes_read == 0)
			break ;
	}
	free(temp);
	line = get_line_from_buffer(&buffer);
	if (error_line(line, &buffer) == NULL)
		return (NULL);
	return (line);
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
