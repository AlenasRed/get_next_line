/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:43:10 by mserjevi          #+#    #+#             */
/*   Updated: 2024/04/25 13:50:02 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
// struct for buffer
char	*get_next_line(int fd)
{
	char			*line;
	static int		current_fd = -1;

	if (current_fd == -1)
		current_fd = fd;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);


	if (fd != current_fd)
		return (NULL);
	line = next(fd);
	if (!line)
		return (NULL);
	return (line);
}
/*
char	*next(char *buffer)
{
	char		*line;
	int			i;
	static int	pos = 0;

	i = line_lenght(buffer + pos);
	if (!i)
		return (NULL);
	line = (char *) malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[pos] != '\n' && buffer[pos] != '\0')
	{
		line[i] = buffer[pos];
		i++;
		pos++;
	}
	if (buffer[pos] == '\n')
	{
		pos++;
		line[i++] = '\n';
	}
	line[i] = '\0';
	return (line);
}*/

char	*next(int fd)
{
	char	*line;
	char	temp[BUFFER_SIZE + 1];
	int		r;

	r = get_buffer(temp, fd);
	line = (char *) malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (r && r != -1)
	{
		line = ft_strjoin(line, temp, r);
		if(temp[r - 1] == '\n')
			return (line);
		r = get_buffer(temp, fd);
		if (r == 0)
			return (line);
	}
	free(line);
	return (NULL);
}

int	get_buffer(char *buff, int fd)
{
	int		r;
	int		i;
	char	c;

	r = read(fd, &c, 1);
	i = 0;
	while(r > 0 && c != '\n')
	{
		buff[i] = c;
		i++;
		if (i >= BUFFER_SIZE)
			break ;
		r = read(fd, &c, 1);
	}
	if (c == '\n')
		buff[i++] = c;
	return (i);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int id;
	char *arr;
	int	r;

	//printf("runed \n");
	id = open("test.txt", O_RDONLY);
	arr = get_next_line(id);
	printf("arr %s", arr);
	while (arr != NULL)
	{

		//char c = 0;
		//r = read(id, &c, 1);
		//printf("c: %d r: %d", c, r);
		arr = get_next_line(id);
		printf("arr inside %s", arr);
		//r = read(id, &c, 1);
		//printf("c: %d r: %d", c, r);

	}
	close (id);
}
