/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/18 12:55:13 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_newline(int fd, char *buffer, int *ov)
{
	
	ssize_t		sz;
	int			c;
	char		tmp_buffer[BUFFER_SIZE + 1];
	char		*nl;

	c = 0;
	(*ov)++;
	sz = read(fd, tmp_buffer, BUFFER_SIZE);
	if (sz == 0)
		return (NULL);
	tmp_buffer[sz] = '\0';
	while (c < sz)
	{
		if (tmp_buffer[c++] == '\n')
		{
			printf("ENDRECURSIONTemp_buffer: %s|<<\nreturn(): %d; Function call: %d\n", tmp_buffer, (int) sz, *ov);
			nl = (char *) malloc(sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			c = -1;
			while (++c < sz)
				buffer[c] = tmp_buffer[c];
			return (nl);
		}
	}
	get_newline(fd, buffer, ov);
	(*ov)--;
	c = sz;
	while (--c >= 0)
		printf("Acces recursive stack values: %c\n",tmp_buffer[c]);
	printf("Temp_buffer: %s|<<\nreturn(): %d; Function call: %d\n", tmp_buffer, (int) sz, *ov);
	return (nl);
}

//returns how many bytes have to be copied
int get_static_buffer(char *buffer)
{
	int		id;
	
	id = 0;
	while (buffer[id] != '\0')
	{
		printf("buffer[%d]=%c", id, buffer[id]);
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
		printf("Neue Zeile einlesen c = %d\n", id);
		get_newline(fd, buffer, &ov);
	}
	// while (c < BUFFER_SIZE + 1)
	// {
	// 	if (buffer[c] != 0)
	// 	{
	// 		printf("\nEs steht was im buffer: %s", buffer);
	// 		printf("\nDie neue Zeile ist: %s", get_static_buffer(buffer));
	// 		printf("\nDer Buffer sieht nun so aus: %s End of FUNCTIONCALL", buffer);
	// 		return (NULL);
	// 	}
	// 	c++;
	// }
	//printf("\nDie neue Zeile ist: %s", get_static_buffer(buffer));
	// printf("Contents of static buffer: %s|<<", buffer);
	return (0);
}
int	main()
{
	int		fd;
	int		sz;
	char	str[] = "A\nB\n";
	
	fd = open("test1.txt", O_RDONLY);
	// printf("Testing the get_static_buffer function. \n Input string: %s", str);
	// printf("\nOutput: %d", get_static_buffer(str));
	//char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	get_next_line(fd);
	get_next_line(fd);
	// get_next_line(fd);
	// printf("Newline check: %d\n",get_newline(fd));
	//printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	//c[sz] = '\0';
	//printf("Those bytes are as follows: %s\n", buffer);
	return (0);
}