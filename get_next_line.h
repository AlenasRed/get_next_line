/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:48 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/03 16:25:15 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_FD 120

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*next(int fd, char *temp, char *buff);
size_t	line_lenght(const char *s);
char	*ft_strjoin(char *s1, char *s2, size_t l1, size_t l2);
int		get_buff_line(int fd, char *temp, char *buff);
char	*mem_alloc(int size);
int		clear_temp(char *temp, int r);
char	*free_mem(char *arr);
#endif