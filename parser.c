#include "minishell.h"

static int	parser_p2(t_all *all, char *str, char **string, int *i)
{
	if (str[*i] == '\'')
		parser_s_quota(string, str, i);
	else if (str[*i] == '\"')
		parser_d_quota(all, string, str, i);
	else if (str[*i] == '\\')
		*string = relloc(*string, str[++(*i)]);
	else if ((str[*i] == ' ' || str[*i] == '\t'))
	{
		if (ft_strncmp(*string, "", 1) && ft_strncmp(*string, "", 1))
			add_arg(all, string);
		skip_spaces(str, i);
	}
	else if (str[*i] == '|')
	{
		if (parser_pipe(all, str, string, i))
			return (1);
	}
	else if (str[*i] == ';')
		parser_semicolon(all, str, string, i);
	else if (str[*i] == '$')
		parser_dollar(all, str, string, i);
	else
		*string = relloc(*string, str[*i]);
	return (0);
}

static void	parser_p3(t_all *all, char *str, char **string, int *i)
{
	if (*i > (int)(ft_strlen(str)))
		*i = ft_strlen(str) + 1;
	if (ft_strncmp(*string, "", 1) && ((str[--(*i)] && (str[*i] != ' '
					&& str[*i] != '\t')) || str[*i] == '\'' || str[*i] == '\"'))
		relloc_args(*string, all);
	if (all->count_pipes)
		all->pipes[all->count_pipes] = all->args;
}

int	parser(char *str, t_all *all)
{
	int		i;
	char	*string;

	i = -1;
	all->count_args = 0;
	string = ft_strdup("");
	skip_spaces(str, &i);
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (parser_redirect(all, str, &string, &i))
				return (1);
		}
		else
		{
			if (parser_p2(all, str, &string, &i))
				break ;
		}
	}
	parser_p3(all, str, &string, &i);
	freed(string);
	return (0);
}
