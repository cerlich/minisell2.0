#include "minishell.h"

static char	*ft_join(char *line, char *buf)
{
	char	*new;
	int		i;

	i = 0;
	while (line[i] != '\0')
		i++;
	new = ft_calloc(i + 2, sizeof(char));
	if (!new)
	{
		printf("minishell: malloc error\n");
		exit(1);
	}
	i = 0;
	while (line[i] != '\0')
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf[0];
	free(line);
	line = NULL;
	return (new);
}

int	get_next_line(int fd, char **line)
{
	char	buf[2];
	int		bytes;

	bytes = 1;
	if (!line || fd < 0)
		return (-1);
	*line = ft_calloc(1, 1);
	while (bytes > 0)
	{
		bytes = read(fd, buf, 1);
		if (buf[0] == '\0' || buf[0] == '\n')
			break ;
		buf[1] = '\0';
		*line = ft_join(*line, buf);
	}
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
	{
		printf("exit\n");
		exit(0);
		return (0);
	}
	return (1);
}
