#include "minishell.h"

void	freed(char *str)
{
	free(str);
	str = NULL;
}

void	d_freed(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		freed(str[i++]);
	free(str);
	str = NULL;
}

void	t_freed(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
		d_freed(str[i++]);
	free(str);
	str = NULL;
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
