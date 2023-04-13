/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:24 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/13 13:43:19 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
	int	BUFFER_SIZE = 100;
#endif
int	main()
{
	int	fd;
	int	sz;
	int	LENGTH = 5;

	fd = open("test1.txt", O_RDONLY);
	char *c = (char *) malloc(BUFFER_SIZE * sizeof(char));
	sz = read(fd, c, LENGTH);
	printf("called read(% d, c, %d). returned that %d bytes were read.\n", fd, LENGTH, sz);
	c[sz] = '\0';
	printf("Those bytes are as follows: %s\n", c);
}