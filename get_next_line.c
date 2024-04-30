/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:43:10 by mserjevi          #+#    #+#             */
/*   Updated: 2024/04/30 20:00:21 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
// struct for buffer
char	*get_next_line(int fd)
{
	char		*line;
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
	char		*line ;
	static char	*temp = NULL;
	//char 		*temp1;
	static int	r;

	if (!temp)
		temp = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	r = get_buffer(temp, fd);
	/*if (line)
	{
		free(line);
		line = NULL;
	}*/
	//if (!line)
	line = (char *) malloc(sizeof(char) * 1);
	if (!line)
	{
		if (temp)
			free(temp);
		return (NULL);
	}
	if (line)
		line[0] = '\0';
	while (r && r != -1)
	{
		//temp1 = line;
		line = ft_strjoin(line, temp, r);
		//free(temp1);
		if (!line)
			return (NULL);
		if (temp[r - 1] == '\n')
			return (line);
		r = get_buffer(temp, fd);
		if (r == 0)
			return (line);
	}
	if (line)
		free(line);
	if (temp)
		free(temp);
	temp = NULL;
	return (NULL);
}

int	get_buffer(char *buff, int fd)
{
	static int		r = 1;
	int				i;
	static char		*temp = NULL;
	static int		pos = 0;

	if (!temp)
		temp = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!temp)
		return (0);
	if (!pos && r > 0)
	{
		clear_temp(temp, r);
		r = read(fd, temp, BUFFER_SIZE);
	}
	i = 0;
	while (r > 0 && pos < r && temp[pos] != '\n' )
	{
		buff[i] = temp[pos];
		i++;
		pos++;
		if (i >= r)
			break ;
	}
	if (r > 0 && pos < r && temp[pos] == '\n')
	{
		buff[i++] = temp[pos];
		pos++;
		if (pos >= r)
			pos = 0;
	}
	else
		pos = 0;
	if (r <= 0 && temp)
	{
		free (temp);
		temp = NULL;
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

	//printf("runed \n");
	id = open("test1.txt", O_RDONLY);
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
}*/
