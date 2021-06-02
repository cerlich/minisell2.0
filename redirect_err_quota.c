#include "minishell.h"

static int	redirect_err(char *file_name, char *str, int *i)
{
	if (file_name[0] == '\0' && str[(*i) + 1] == '>')
		write(1, "minishell: syntax error near unexpected token `>>'\n", 51);
	else if (file_name[0] == '\0' && str[*i] == '<')
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
	else if (file_name[0] == '\0')
		write(1, "minishell: syntax error near unexpected token `>'\n", 50);
	else
		printf("minishell: syntax error near unexpected token `%s'\n",
			file_name);
	free(file_name);
	return (1);
}

static int	is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

static int	red_s_quota(char *str, int *i, char **file_name)
{
	char	*quota;

	quota = simple_quota(str, i);
	*file_name = ft_strjoin(*file_name, quota);
	freed(quota);
	return (1);
}

static int	red_d_quota(char *str, int *i, char **file_name, t_all *all)
{
	char	*quota;

	quota = double_quota(str, i, all);
	*file_name = ft_strjoin(*file_name, quota);
	freed(quota);
	return (1);
}

int	red_while(char *str, int *i, char **file_name, t_all *all)
{
	int		f;

	f = 0;
	if (str[*i] == '\'')
		f = red_s_quota(str, i, file_name);
	else if (str[*i] == '\"')
		f = red_d_quota(str, i, file_name, all);
	else if (str[*i] == '\\')
		*file_name = relloc(*file_name, str[++(*i)]);
	else if ((str[*i] == '>' || str[*i] == '<') && !f && is_num(*file_name))
		return (redirect_err(*file_name, str, i));
	else if (str[*i] == '>' && (str[(*i) + 1] == ' '
			|| str[(*i) + 1] == '\t' || !str[(*i) + 1]))
	{
		write(1,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		free(*file_name);
		return (1);
	}
	else
		*file_name = relloc(*file_name, str[*i]);
	return (0);
}
