/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calberti <calberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:06:24 by calberti          #+#    #+#             */
/*   Updated: 2025/03/19 14:17:24 by calberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int			ft_strlen(char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*get_line_from_buffer(char **buffer);
char		*get_next_line(int fd);
char		*ft_strchr_gnl(const char *s, int c);
char		*f_strchr(char *s, int c);
char		*f_strdup(char *s1);
char		*f_strjoin(char *s1, char *s2);
int			ft_malloc_count(char *stock);
char		*ft_get_the_line(char *stock);
void		ft_get_the_spare(char *buffer);
char		*ft_line_results(int ret, char *stock, char *buffer);
char		*get_next_line(int fd);

#endif
