#include "minishell.h"

void	parser_s_quota(char **string, char *str, int *i)
{
	char	*tmp;

	tmp = simple_quota(str, i);
	*string = ft_strjoin(*string, tmp);
	freed(tmp);
}

void	parser_d_quota(t_all *all, char **string, char *str, int *i)
{
	char	*tmp;

	tmp = double_quota(str, i, all);
	*string = ft_strjoin(*string, tmp);
	freed(tmp);
}

int	parser_redirect(t_all *all, char *str, char **string, int *i)
{
	if (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\t'
		&& ft_strncmp(*string, "", 1))
		add_arg(all, string);
	if (redirect(str, i, all))
	{
		d_freed(all->args);
		freed(*string);
		return (1);
	}
	skip_spaces(str, i);
	(*i)--;
	return (0);
}
