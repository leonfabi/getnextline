/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/19 11:25:25 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*shift_stat_buffer(char *buffer, char *tmp_buffer, int c, int cpy)
{
	int	shift;

	shift = -1;
	printf("\t\t\tshift_stat_buffer_call, Index:>>|%i|<<\n", c);
	while (tmp_buffer[++shift] && cpy)
	{
		// printf("\t\t\tWhile tmp_buffer[%i]:%c|<<\n", shift, tmp_buffer[shift]);
		buffer[shift] = tmp_buffer[shift];
	}
	printf("\t\t\ttmp_buffer:>>|%s|<<\n", tmp_buffer);
	shift = -1;
	while (buffer[++shift])
	{
		// printf("\t\t\tWhile buffer[%i]:%c|<<\n", shift, buffer[shift]);
		if ((c + shift) > BUFFER_SIZE)
			buffer[shift] = '\0';
		else
			buffer[shift] = tmp_buffer[shift + c];
	}
	printf("\t\t\tstatic buffer:>>|%s|<<\n", buffer);
	return (buffer);
}
char *get_newline(int fd, char *buffer, int *ov, int id)
{
	
	ssize_t		sz;
	int			c;
	char		tmp_buffer[BUFFER_SIZE + 1];
	char		*nl;

	c = 0;
	(*ov)++;
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	//printf("SZ: %ld\n", sz);
	if (sz == 0)
		return (NULL);
	tmp_buffer[sz] = '\0';
	while (c < sz)
	{
		if (tmp_buffer[c++] == '\n')
		{
			printf("\t\tMemory allocation\n\t\ttmp_buffer: %s\n", tmp_buffer);
			nl = (char *) malloc(id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = '\0';
			while (--id >= 0)
				nl[id] = buffer[id];
			printf("\t\tEnd of Recursion, static_buffer:>>|%s|<<\n",shift_stat_buffer(buffer, tmp_buffer, c, 1));
			while (--c >=0)
				nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
			return (nl);
		}
	}
	nl = get_newline(fd, buffer, ov, id);
	(*ov)--;
	c = sz;
	while (--c >= 0)
		nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
	return (nl);
}

//returns how many bytes have to be copied
int get_static_buffer(char *buffer)
{
	int		id;
	
	id = 0;
	while (buffer[id] != '\0')
	{
		//printf("buffer[%d]=%c", id, buffer[id]);
		if (buffer[id] == '\n')
			return (id + 1);
		id++;
	}
	return (id);
}
char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			id;
	int			ov;

	id = get_static_buffer(buffer);
	ov = 0;
	if (id == 0 || (id == BUFFER_SIZE && buffer[id] == '\n'))
	{
		printf("\tNeue Zeile einlesen c = %d\n", id);
		return (get_newline(fd, buffer, &ov, id));
	}
	else
	{
		printf("\tStatischer buffer> %s\n",buffer);
		return (shift_stat_buffer(buffer, buffer, id, 0));
	}
	return (0);
}
#include <string.h>
int	main()
{
	int		fd;
	int		sz;
	char	str[] = "AB\nC\nDE\nF";
	
	fd = open("test1.txt", O_RDONLY);
	// printf("Testing the get_static_buffer function. \n Input string: %s", str);
	// printf("\nOutput: %d", get_static_buffer(str));
	//char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	printf("File : >>%s<<\nBuffersize: %d\nFile length: %li\n", str, BUFFER_SIZE, strlen(str));
	printf("Line to print: %s|<<\n",get_next_line(fd));
	printf("Line to print: %s|<<\n",get_next_line(fd));
	// printf("Line to print: %s|<<\n",get_next_line(fd));
	// printf("Line to print: %s|<<\n",get_next_line(fd));
	// printf("Line to print: %s|<<\n",get_next_line(fd));
	//get_next_line(fd);
	// get_next_line(fd);
	// printf("Newline check: %d\n",get_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}