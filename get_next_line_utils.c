/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:42 by mserjevi          #+#    #+#             */
/*   Updated: 2024/04/25 13:18:04 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

size_t	line_lenght(const char *s)
{
	size_t	l;

	l = 0;
	while (*s && *s != '\n')
	{
		l++;
		s++;
	}
	if (*s == '\n')
		l++;
	return (l);
}

void	ft_strcpyf(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	free(src);
}

char	*ft_strjoin(char *s1, char *s2, size_t l2)
{
	size_t	l1;
	//size_t	l2;
	size_t	i;
	char	*str;

	l1 = ft_strlen(s1);
	//l2 = ft_strlen(s2);
	i = 0;
	str = (char *) malloc (sizeof(char) * (l1 + l2 + 1));
	if (str == NULL)
		return (NULL);
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		str[i] = s2[i - l1];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}
