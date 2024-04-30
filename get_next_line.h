/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:48 by mserjevi          #+#    #+#             */
/*   Updated: 2024/04/30 14:49:25 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	line_lenght(const char *s);
int		get_char(char *buffer);
size_t	ft_strlen(const char *s);
void	ft_strcpyf(char *dst, char *src);
char	*next(int fd);
char	*ft_strjoin(char *s1, char *s2, size_t l2);
int		get_buffer(char *buff, int fd);
void 	clear_temp(char *temp);
#endif