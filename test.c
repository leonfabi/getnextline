/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/17 12:17:41 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int is_newline(int fd, char *buffer)
{
	
	ssize_t		sz;
	int			counter;
	char		tmp_buffer[BUFFER_SIZE + 1];

	counter = 0;
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	while (tmp_buffer[counter])
	{
		if (tmp_buffer[counter++] == '\n')
		{
			printf("Temp_buffer: %s\nreturn(): %d\n", tmp_buffer, (int) sz);
			counter = -1;
			while (tmp_buffer[++counter])
				buffer[counter] = tmp_buffer[counter];
			return (1);
		}
	}
	is_newline(fd, buffer);
	printf("Temp_buffer: %s\nreturn(): %d\n", tmp_buffer, (int) sz);
}

int	main()
{
	int		fd;
	int		sz;
	int		counter = 0;
	static char buffer[BUFFER_SIZE + 1];

	buffer[BUFFER_SIZE] = '\0';
	fd = open("test1.txt", O_RDONLY);
	//char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	is_newline(fd, buffer);
	printf("Contents of static buffer: %s", buffer);
	// printf("Newline check: %d\n",is_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}