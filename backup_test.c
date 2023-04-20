/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:50:55 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/20 16:01:25 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*shift_stat_buffer(char *buffer, char *tmp_buffer, int c, int cpy)
{
	int	shift;

	shift = -1;
	while (tmp_buffer[++shift] && cpy)
		buffer[shift] = tmp_buffer[shift];
	shift = -1;
	while (buffer[++shift])
	{
		if ((c + shift) > BUFFER_SIZE)
			buffer[shift] = '\0';
		else
			buffer[shift] = tmp_buffer[shift + c];
	}
	return (buffer);
}

int		read_fd(int fd, char *tmp_buffer)
{
	ssize_t		sz;

	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	if (sz < 0)
		return (-1);
	else
	{
		if (sz >= 0)
			tmp_buffer[sz] = '\0';
		sz = 0;
		while (tmp_buffer[sz] != '\0' && tmp_buffer[sz] != '\n')
			sz++;
	}
	return (sz);
}

char	*get_newline(int fd, char *buffer, int size)
{
	ssize_t		sz;
	ssize_t		c;
	char		tmp_buffer[BUFFER_SIZE + 1];
	char		*nl;

	c = 0;
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	if (sz >= 0)
		tmp_buffer[sz] = '\0';
	while (tmp_buffer[c] != '\0' && tmp_buffer[c] != '\n')
		c++;
	if (tmp_buffer[c] != '\n' && sz > 0)
		nl = get_newline(fd, buffer, size + sz);
	else if ((size == 0 && sz == 0) || sz == -1)
		return (NULL);
	else
	{
		if (tmp_buffer[c] == '\n')
			c++;
		nl = (char *) malloc(sizeof(char) * (size + 1 + c));
		if (nl == NULL)
			return (NULL);
		nl[size + c] = '\0';
		shift_stat_buffer(buffer, tmp_buffer, c, 1);
	}
	while (--c >= 0)
		nl[size + c] = tmp_buffer[c];
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
	char		t_bf[BUFFER_SIZE + 1];
	int			id;
	char		*nl;

	id = -1;
	while (++id <= BUFFER_SIZE)
		t_bf[id] = buffer[id];
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
		while (--id >= 0)
			nl[id] = t_bf[id];
		return (nl);
	}
	return (0);
}
