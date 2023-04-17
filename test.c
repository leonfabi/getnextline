/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/17 13:41:03 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *is_newline(int fd, char *buffer, int *ov, char *nl)
{
	
	ssize_t		sz;
	int			c;
	char		tmp_buffer[BUFFER_SIZE + 1];

	c = 0;
	(*ov)++;
	tmp_buffer[BUFFER_SIZE] = '\0';
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	while (tmp_buffer[c])
	{
		if (tmp_buffer[c++] == '\n')
		{
			printf("ENDRECURSIONTemp_buffer: %s|--end\nreturn(): %d; Function call: %d\n", tmp_buffer, (int) sz, *ov);
			nl = (char *) malloc(sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			c = -1;
			while (++c )
				buffer[c] = tmp_buffer[c];
			return (nl);
		}
	}
	is_newline(fd, buffer, ov, nl);
	(*ov)--;
	printf("Temp_buffer: %s|--end\nreturn(): %d; Function call: %d\n", tmp_buffer, (int) sz, *ov);
	return (nl);
}

int	main()
{
	int		fd;
	int		sz;
	static char buffer[BUFFER_SIZE + 1];
	int		ov;
	char	*nl;

	buffer[BUFFER_SIZE] = '\0';
	ov = 0;
	nl = NULL;
	fd = open("test1.txt", O_RDONLY);
	//char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	is_newline(fd, buffer, &ov, nl);
	printf("Contents of static buffer: %s|--end", buffer);
	// printf("Newline check: %d\n",is_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}