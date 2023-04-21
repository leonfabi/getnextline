/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:30:51 by fkrug             #+#    #+#             */
/*   Updated: 2023/04/21 13:38:03 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	read_fd(int fd, char *tmp_buf, char *buffer)
{
	ssize_t		sz;

	sz = read(fd, tmp_buf, BUFFER_SIZE);
	if (sz < 0 || sz > BUFFER_SIZE)
	{
		buffer[0] = '\0';
		return (-1);
	}
	else if (sz >= 0)
		tmp_buf[sz] = '\0';
	return (sz);
}
