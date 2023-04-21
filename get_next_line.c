/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:50:55 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/21 08:47:04 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*shift_stat_buffer(char *buffer, char *tmp_buf, int c, int cpy)
{
	int	shift;

	shift = -1;
	while (tmp_buf[++shift] && cpy)
		buffer[shift] = tmp_buf[shift];
	shift = -1;
	while (buffer[++shift])
	{
		if ((c + shift) > BUFFER_SIZE)
			buffer[shift] = '\0';
		else
			buffer[shift] = tmp_buf[shift + c];
	}
	return (buffer);
}

ssize_t		read_fd(int fd, char *tmp_buf, char *buffer)
{
	ssize_t		sz;

	sz = read(fd, tmp_buf, BUFFER_SIZE);
	if (sz < 0 || sz > BUFFER_SIZE)
	{
		buffer[0] = '\0';
		return (-1);
	}
	else
	{
		if (sz >= 0)
			tmp_buf[sz] = '\0';
		//sz = 0;
		//while (tmp_buf[sz] != '\0' && tmp_buf[sz] != '\n')
		//	sz++;
	}
	return (sz);
}

char	*get_newline(int fd, char *buffer, int size)
{
	ssize_t		sz;
	ssize_t		c;
	char		tmp_buf[BUFFER_SIZE + 1];
	char		*nl;

	c = 0;
	sz = read_fd(fd, tmp_buf, buffer);
	while (tmp_buf[c] != '\0' && tmp_buf[c] != '\n')
		c++;
	if (tmp_buf[c] != '\n' && sz > 0)
	{
		nl = get_newline(fd, buffer, size + c);
		if (nl == NULL)
			return (NULL);
	}
	else if ((size == 0 && sz == 0) || sz == -1)
		return (NULL);
	else
	{
		if (tmp_buf[c] == '\n')
			c++;
		nl = (char *) malloc(sizeof(char) * (size + 1 + c));
		if (nl == NULL)
			return (NULL);
		nl[size + c] = '\0';
		shift_stat_buffer(buffer, tmp_buf, c, 1);
	}
	while (--c >= 0)
		nl[size + c] = tmp_buf[c];
	return (nl);
}
char	*get_newline_from_buffer(char *buffer, int id)
{
	int		c_id;
	char	*nl;

	c_id = id + 1;
	(id)++;
	nl = (char *)malloc(id * sizeof(char) + 1);
	if (nl == NULL)
		return (NULL);
	nl[c_id] = '\0';
	while (--c_id >= 0)
		nl[c_id] = buffer[c_id];
	shift_stat_buffer(buffer, buffer, id, 1);
	return (nl);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		tmp_buf[BUFFER_SIZE + 1];
	int			id;
	char		*nl;
	
	id = -1;
	while (++id <= BUFFER_SIZE)
		tmp_buf[id] = buffer[id];
	id = 0;
	nl = NULL;
	if (fd < 0 || fd > 256 || BUFFER_SIZE < 1)
		return (NULL);
	while (buffer[id] != '\0' && buffer[id] != '\n')
		id++;
	if (buffer[id] == '\n')
		return (get_newline_from_buffer(buffer, id));
	else
	{
		nl = get_newline(fd, buffer, id);
		while (--id >= 0 && nl != NULL)
			nl[id] = tmp_buf[id];
		return (nl);
	}
	return (0);
}
