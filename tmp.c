char *get_static_buffer(char *buffer)
{
	int		c;
	char	*nl;
	int		fill;
	
	c = 0;
	fill = -1;
	while (buffer[c] != '\0' && buffer[c] != '\n')
		c++;
	if (buffer[c] == '\0')
		c--;
	nl = (char *)malloc(sizeof(char) * (c + 2));
	if (nl == NULL)
		return (NULL);
	while (buffer[++fill])
	{
		if (fill <= c)
			nl[fill] = buffer[fill];
		if ((c + fill + 1) > BUFFER_SIZE)
			buffer[fill] = '\0';
		else
			buffer[fill] = buffer[fill + c + 1];
	}
	nl[fill] = '\0';
	return (nl);
}