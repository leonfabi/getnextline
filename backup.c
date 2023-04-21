char	*get_newline(int fd, char *buffer, int size)
{
	ssize_t		sz;
	ssize_t		c;
	char		t_bf[BUFFER_SIZE + 1];
	char		*nl;

	c = 0;
	sz = read(fd, t_bf, BUFFER_SIZE);
	if (sz < 0 || sz > BUFFER_SIZE)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	if (sz >= 0)
		t_bf[sz] = '\0';
	while (t_bf[c] != '\0' && t_bf[c] != '\n')
		c++;
	if (t_bf[c] != '\n' && sz > 0)
	{
		nl = get_newline(fd, buffer, size + c);
		if (nl == NULL)
			return (NULL);
	}
	else if ((size == 0 && sz == 0) || sz == -1)
		return (NULL);
	else
	{
		if (t_bf[c] == '\n')
			c++;
		nl = (char *) malloc(sizeof(char) * (size + 1 + c));
		if (nl == NULL)
			return (NULL);
		nl[size + c] = '\0';
		shift_stat_buffer(buffer, t_bf, c, 1);
	}
	while (--c >= 0)
		nl[size + c] = t_bf[c];
	return (nl);
}