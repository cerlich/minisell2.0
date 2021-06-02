#include "minishell.h"

void	freed(void *content)
{
	free(content);
	content = NULL;
}

void	d_freed(void *content)
{
	int				i;
	unsigned char	**d_arr;

	d_arr = (unsigned char **)content;
	i = 0;
	while (d_arr[i])
		freed(d_arr[i++]);
	free(d_arr);
	d_arr = NULL;
}

void	t_freed(void *content)
{
	int				i;
	unsigned char	***t_arr;

	t_arr = (unsigned char ***)content;
	i = 0;
	while (t_arr[i])
		d_freed(t_arr[i++]);
	free(t_arr);
	t_arr = NULL;
}

int	ft_strclen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i + 1);
}

int	find_overlap(char **s1, char *s2)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strclen(s2, '=');
	while (s1[++i])
	{
		if (!ft_strncmp(s1[i], s2, len))
			return (i);
	}
	return (-1);
}
