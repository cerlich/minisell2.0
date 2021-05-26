/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:02:21 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/05/24 14:46:02 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_line(int fd, char **stat, char **line)
{
	int		i;
	char	*buf;

	i = 0;
	if (!(buf = (char*)malloc(sizeof(char) + 1)))
		return (0);
	while ((i = read(fd, buf, 1)) != -1)
	{
		if (i == 0)
		{
			free(buf);
			write(1, " exit\n", 5);
			free(*line);
			*line = NULL;
			line = NULL;
			exit(0);
		}
		buf[i] = '\0';
		if (buf[i - 1] == '\n')
			return (1);
		*stat = ft_add(*stat, buf);
	}
	free(buf);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	size_t		j;
	static char	*stat;

	if (fd < 0 || !line || !(read_line(fd, &stat, line)))
		return (-1);

	if (!stat)
	{
		*line = get_line("\0");
		return (0);
	}
	j = 0;
	while (stat[j])
	{
		if (stat[j] == '\n')
		{
			*line = get_line(stat);
			stat = get_put(stat);
			return (1);
		}
		j++;
	}
	*line = get_line(stat);
	stat = get_put(stat);
	return (0);
}
