/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:50:55 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/20 17:29:40 by fkrug            ###   ########.fr       */
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

ssize_t		read_fd(int fd, char *tmp_buffer)
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
		nl = get_newline(fd, buffer, size + c);
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

#include <string.h>
#include <signal.h>
void handle_sigsegv(int signal) {
    printf("Segmentation fault\n");
    exit(EXIT_FAILURE);
}

int	main()
{
	int		fd;
	int		sz;	
	//###############
	FILE *fptr;
	signal(SIGSEGV, handle_sigsegv);
	char c;
	// Open file
	fptr = fopen("test1.txt", "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	// Read contents from file
	c = fgetc(fptr);
	printf("File:>>|");
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(fptr);
	}

	fclose(fptr);
	//###############
	fd = open("test1.txt", O_RDONLY);
	// printf("Testing the get_static_buffer function. \n Input string: %s", str);
	// printf("\nOutput: %d", get_static_buffer(str));
	//char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	printf("|<<\nBuffersize: %d\n", BUFFER_SIZE);
	printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	// printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	// printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	//get_next_line(fd);
	// get_next_line(fd);
	// printf("Newline check: %d\n",get_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}