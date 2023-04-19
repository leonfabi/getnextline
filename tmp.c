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
		get_newline(fd, buffer, &ov, id);
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

char *get_newline(int fd, char *buffer, int *ov, int id)
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
			nl = (char *) malloc(id + sizeof(char) * (*ov - 1) * BUFFER_SIZE + c + 1);
			nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = '\0';
			while (--c >=0)
				nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
			// c = -1;
			// while (++c < sz)
			// 	buffer[c] = tmp_buffer[c];
			return (nl);
		}
	}
	nl = get_newline(fd, buffer, ov);
	(*ov)--;
	c = sz;
	while (--c >= 0)
	{
		printf("Return value: %s Acces recursive stack values: %c at index: %d\n", nl,tmp_buffer[c], c);
		nl[sizeof(char) * (*ov - 1) * BUFFER_SIZE + c] = tmp_buffer[c];
	}
	printf("Temp_buffer: %s|<<\nreturn(): %d; Function call: %d\n", tmp_buffer, (int) sz, *ov);
	return (nl);
}