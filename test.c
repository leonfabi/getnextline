/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/20 11:45:08 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*shift_stat_buffer(char *buffer, char *tmp_buffer, int *c, int cpy)
{
	int	shift;

	shift = -1;
	while (tmp_buffer[++shift] && cpy)
		buffer[shift] = tmp_buffer[shift];
	shift = -1;
	while (buffer[++shift])
	{
		if ((*c + shift) > BUFFER_SIZE)
			buffer[shift] = '\0';
		else
			buffer[shift] = tmp_buffer[shift + *c];
	}
	return (buffer);
}
char *get_newline(int fd, char *buffer, int *ov, int *id)
{
	
	ssize_t		sz;
	int			c;
	char		tmp_buffer[BUFFER_SIZE + 1];
	char		*nl;
	int			c_id;

	c = 0;
	c_id = *id;
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	(*ov)++;
	tmp_buffer[sz] = '\0';
	while (c < sz)
	{
		if (tmp_buffer[c++] == '\n')
		{
			nl = (char *) malloc(*id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			nl[*id +sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = '\0';
			while (--(c_id) >= 0)
				nl[c_id] = buffer[c_id];
			shift_stat_buffer(buffer, tmp_buffer, &c, 1);
			while (--c >= 0)
				nl[*id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
			return (nl);
		}
	}
	if (sz == 0)
	{
		if ((*ov - 1) == 0 && *id == 0)
			return (NULL);
		else
		{
			nl = (char *) malloc(*id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			nl[*id +sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = '\0';
			while (--(c_id) >= 0)
				nl[c_id] = buffer[c_id];
			shift_stat_buffer(buffer, tmp_buffer, &c, 1);
			while (--c >= 0)
				nl[*id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
			return (nl);
		}
	}
	nl = get_newline(fd, buffer, ov, id);
	(*ov)--;
	c = sz;
	while (--c >= 0)
		nl[*id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
	return (nl);
}

//returns how many bytes have to be copied
int get_static_buffer(char *buffer, int *id)
{
	while (buffer[*id] != '\0')
	{
		if (buffer[*id] == '\n')
			return (0);
		(*id)++;
	}
	return (1);
}
char *get_newline_from_buffer(char *buffer, int *id)
{
	int		c_id;
	char	*nl;

	c_id = *id + 1;
	(*id)++;
	nl = (char *)malloc(*id * sizeof(char) + 1);
	if (nl == NULL)
		return (NULL);
	nl[c_id] = '\0';
	while (--c_id >= 0)
		nl[c_id] = buffer[c_id];
	shift_stat_buffer(buffer, buffer, id, 1);
	return (nl);
}
char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			id;
	int			ov;
	int			newline;

	id = 0;
	newline = get_static_buffer(buffer, &id);
	ov = 0;
	if (fd < 0 || fd > 256 || BUFFER_SIZE < 1)
		return (NULL);
	if (newline)
		return (get_newline(fd, buffer, &ov, &id));
	else
		return (get_newline_from_buffer(buffer, &id));
	return (0);
}

#include <string.h>
int	main()
{
	int		fd;
	int		sz;	
	//###############
	FILE *fptr;

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
	printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	printf("Line to print: >>|%s|<<\n",get_next_line(fd));
	//get_next_line(fd);
	// get_next_line(fd);
	// printf("Newline check: %d\n",get_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}