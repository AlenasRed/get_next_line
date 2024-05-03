/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:43:10 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/03 16:27:38 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	*temp[MAX_FD];
	static char	*buff[MAX_FD];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!temp[fd])
		temp[fd] = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp[fd])
		return (NULL);
	if (!buff[fd])
		buff[fd] = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff[fd])
		return (temp[fd] = free_mem(temp[fd]));
	line = next(fd, temp[fd], buff[fd]);
	if (!line)
	{
		if (temp[fd])
			temp[fd] = free_mem(temp[fd]);
		if (buff[fd])
			buff[fd] = free_mem(buff[fd]);
		return (NULL);
	}
	return (line);
}

char	*next(int fd, char *temp, char *buff)
{
	int		r;
	int		l;
	char	*line;

	l = 0;
	line = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	r = get_buff_line(fd, temp, buff);
	line[0] = '\0';
	while (r > 0)
	{
		line = ft_strjoin(line, temp, l, r);
		l += r;
		if (!line)
			return (NULL);
		if (temp[r - 1] == '\n')
			return (line);
		r = get_buff_line(fd, temp, buff);
		if (r == 0)
			return (line);
	}
	free(line);
	return (NULL);
}

int	get_buff_line(int fd, char *temp, char *buff)
{
	static int		r = 1;
	int				i;
	static int		pos = 0;

	if (!pos && r > 0 && clear_temp(buff, r))
		r = read(fd, buff, BUFFER_SIZE);
	i = 0;
	while (r > 0 && pos < r && buff[pos] != '\n' )
		temp[i++] = buff[pos++];
	if (r > 0 && pos < r && buff[pos] == '\n')
	{
		temp[i++] = buff[pos++];
		if (pos >= r)
			pos = 0;
	}
	else
		pos = 0;
	if (r <= 0)
	{
		i = r;
		r = 1;
	}
	return (i);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int id;
	char *arr;

	id = open("test1.txt", O_RDONLY);
	arr = get_next_line(id);
	printf("arr %s", arr);
	free(arr);
	while (arr != NULL)
	{
		arr = get_next_line(id);
		printf("arr inside %s", arr);
		free(arr);
	}
    close(id);
    id = open("test1.txt", O_RDONLY);
	arr = get_next_line(id);
	printf("arr %s", arr);
	free(arr);
	while (arr != NULL)
	{
		arr = get_next_line(id);
		printf("arr inside %s", arr);
		free(arr);
	}
    close(id);
}*/