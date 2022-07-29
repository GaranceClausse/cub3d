/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:17:42 by myrmarti          #+#    #+#             */
/*   Updated: 2022/07/29 11:56:10 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


# include <ctype.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../../libft/libft.h"

char	*ft_realloc(char *line, char *buff);

/*
int		copy_after_nl(char *str);
int		error(int fd, char *buff);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *s);

char	*ft_realloc(char *line, char *buff);
char	*ft_strchr(const char *s, int c);

void	*ft_memset( void *pointer, int value, size_t count);
void	*ft_memcpy(void *dest, void *src, size_t n);
*/
#endif