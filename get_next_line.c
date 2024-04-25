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
//#include <stdio.h>
// struct for buffer
char	*get_next_line(int fd)
{
	static char		*buffer = NULL;
	char			*line;
	static int		current_fd = -1;

	if (current_fd == -1)
		current_fd = fd;
	if (fd < 0 || fd > 20 || BUFFER_SIZE <= 0)
	{
		//close(fd);
		return (NULL);
	}
	if (buffer == NULL)
		buffer = get_buffer(fd);

	if (fd != current_fd)
	{
		free(buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = next(buffer);
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	return (line);
}

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
}

char	*get_buffer(int fd)
{
	char	*buffer;
	char	*temp;
	int		r;

	r = 1;
	temp = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp || !buffer)
		return (NULL);
	buffer[0] = '\0';
	r = read(fd, temp, BUFFER_SIZE);
	while (r && r != -1)
	{
		temp[r] = '\0';
		buffer = ft_strjoin(buffer, temp);
		r = read(fd, temp, BUFFER_SIZE);
		if (r == 0)
		{
			free(temp);
			return (buffer);
		}
	}
	free(buffer);
	free(temp);
	return (NULL);
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
		arr = get_next_line(id);
		printf("arr inside %s", arr);

	}
	close (id);
}*/
