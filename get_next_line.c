/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:43:10 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/03 17:47:04 by mserjevi         ###   ########.fr       */
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
	int		temp_len;
	int		line_len;
	char	*line;

	line_len = 0;
	line = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	temp_len = get_buff_line(fd, temp, buff);
	line[0] = '\0';
	while (temp_len > 0)
	{
		line = ft_strjoin(line, temp, line_len, temp_len);
		line_len += temp_len;
		if (!line)
			return (NULL);
		if (temp[temp_len - 1] == '\n')
			return (line);
		temp_len = get_buff_line(fd, temp, buff);
		if (temp_len == 0)
			return (line);
	}
	free(line);
	return (NULL);
}

int	get_buff_line(int fd, char *temp, char *buff)
{
	static int		read_len = 1;
	int				i;
	static int		buff_pos = 0;

	if (!buff_pos && read_len > 0 && clear_temp(buff, read_len))
		read_len = read(fd, buff, BUFFER_SIZE);
	i = 0;
	while (read_len > 0 && buff_pos < read_len && buff[buff_pos] != '\n' )
		temp[i++] = buff[buff_pos++];
	if (read_len > 0 && buff_pos < read_len && buff[buff_pos] == '\n')
	{
		temp[i++] = buff[buff_pos++];
		if (buff_pos >= read_len)
			buff_pos = 0;
	}
	else
		buff_pos = 0;
	if (read_len <= 0)
	{
		i = read_len;
		read_len = 1;
	}
	return (i);
}
