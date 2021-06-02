#include "minishell.h"

static char	*vopros(t_all *all, int *j, char **new)
{
	char	*tmp;

	tmp = ft_itoa(all->pid->status_exit);
	*new = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	*j += 1;
	return (*new);
}

static int	key(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] == '_' || ft_isalnum(str[i]))
	{
		n++;
		i++;
	}
	return (n);
}

char	*treat_dollar(char *str, int *j, t_all *all)
{
	char	*new;
	int		i;
	int		n;

	i = -1;
	n = key(&str[1]);
	*j += n;
	if (!ft_strncmp(&str[1], "?", 2))
		return (vopros(all, j, &new));
	while (all->envp[++i])
	{
		if (!ft_strncmp(all->envp[i], &str[1], n) && all->envp[i][n] == '=')
		{
			new = ft_strdup(&all->envp[i][n + 1]);
			return (new);
		}
	}
	new = ft_strdup("");
	return (new);
}

void	parser_dollar(t_all *all, char *str, char **string, int *i)
{
	char	*tmp;

	if (ft_isalpha(str[(*i) + 1]))
		tmp = treat_dollar(&str[*i], i, all);
	else if (str[(*i) + 1] == '?')
		tmp = treat_dollar(&str[*i], i, all);
	else
		tmp = relloc(ft_strdup(""), str[*i]);
	*string = ft_strjoin(*string, tmp);
	freed(tmp);
}
