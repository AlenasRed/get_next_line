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

	if (fd < 0 || fd > 20 || BUFFER_SIZE <= 0)
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
	static char	*temp[20];
	//char 		*temp1;
	static int	r;

	if (!temp[fd])
		temp[fd] = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp[fd])
		return (NULL);
	r = get_buffer(temp[fd], fd);
   // printf("R : %d\n", r);
	/*if (line)
	{
		free(line);
		line = NULL;
	}*/
	//if (!line)
	line = (char *) malloc(sizeof(char) * 1);
	if (!line)
	{
		if (temp[fd])
			free(temp[fd]);
		return (NULL);
	}
	if (line)
		line[0] = '\0';
	while (r > 0)
	{
		//temp1 = line;
		line = ft_strjoin(line, temp[fd], r);
		//free(temp1);
		if (!line)
			return (NULL);
		if (temp[fd][r - 1] == '\n')
			return (line);
		r = get_buffer(temp[fd], fd);
		if (r == 0)
			return (line);
	}
	if (line)
		free(line);
    if (temp[fd])
    {
		free(temp[fd]);
	    temp[fd] = NULL;
    }
	return (NULL);
}

int	get_buffer(char *buff, int fd)
{
	static int		r = 1;
	int				i;
	static char		*temp[20];
	static int		pos = 0;

	if (!temp[fd])
		temp[fd] = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!temp[fd])
		return (0);
	if (!pos && r > 0)
	{
		clear_temp(temp[fd], r);
		r = read(fd, temp[fd], BUFFER_SIZE);
        if (r == -1)
        {
            free (temp[fd]);
		    temp[fd] = NULL;
            r = 1;
            return (-1);
        }
	}
	i = 0;
	while (r > 0 && pos < r && temp[fd][pos] != '\n' )
	{
		buff[i] = temp[fd][pos];
		i++;
		pos++;
		if (i >= r)
			break ;
	}
	if (r > 0 && pos < r && temp[fd][pos] == '\n')
	{
		buff[i++] = temp[fd][pos];
		pos++;
		if (pos >= r)
			pos = 0;
	}
	else
		pos = 0;
	if (r <= 0 && temp[fd])
	{
		free (temp[fd]);
		temp[fd] = NULL;
        if (r == -1)
            return (-1);
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
    close(id);
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