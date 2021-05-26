#include "minishell.h"

int		not_spec(char c)
{
	if (c == ' ')
		return (0);
	if (c == '\0')
		return (0);
	if (c == ';')
		return (0);
	if (c == '|')
		return (0);
	if (c == '\t')
		return (0);
	return (1);
}
// ls >1>	ls >:>		ls >''1>	ls >1>
void	redirect_err(char *file_name, char *str, int *i)
{
	if (file_name[0] == '\0' && str[(*i) + 1] == '>')
		write(1, "minishell: syntax error near unexpected token `>>'\n", 51);
	else if (file_name[0] == '\0' && str[*i] == '<')
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
	else if (file_name[0] == '\0')
		write(1, "minishell: syntax error near unexpected token `>'\n", 50);
	else
		printf("minishell: syntax error near unexpected token `%s'\n", file_name);
	exit(EXIT_FAILURE);
}

int		check_redirect(char *str, int *i)
{
	if (str[*i] == '<')
		return (2);
	if (str[(*i) + 1] == '>')
	{
		(*i)++;
		return (1);
	}
	return 0;
}

int		is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	redirect(char *str, int *i, t_all *all)
{
	char	*file_name;
	char	*quota;
	int		fd_1;
	int		fd_2;
	int		redirect;
	int		f;

	redirect = 0;
	f = 0;
	file_name = ft_strdup("");
	redirect = check_redirect(str, i);
	skip_spaces(str, i);
	if (!str[(*i) + 1])
	{
		write(1, "minishell: syntax error near unexpected token `newline'\n", 56);
		exit(EXIT_FAILURE);
	}
	while (not_spec(str[++(*i)]))
	{
		if (str[*i] == '\'')
		{
			quota = simple_quota(str, i);
			file_name = ft_strjoin(file_name, quota);
			freed(quota);
			f = 1;
		}
		else if (str[*i] == '\"')
		{
			quota = double_quota(str, i, all);
			file_name = ft_strjoin(file_name, quota);
			freed(quota);
			f = 1;
		}
		else if (str[*i] == '\\')
			file_name = relloc(file_name, str[++(*i)]);
		else if ((str[*i] == '>' || str[*i] == '<') && !f && is_num(file_name))
			redirect_err(file_name, str, i);
		else if (str[*i] == '>' && (str[(*i) + 1] == ' ' || str[(*i) + 1] == '\t' || !str[(*i) + 1]))
		{
			write(1, "minishell: syntax error near unexpected token `newline'\n", 56);
			exit(EXIT_FAILURE);
		}
		else
			file_name = relloc(file_name, str[*i]);
	}
	// change_dir
	if (redirect == 0)
	{
		close(all->redirect_1);
		fd_1 = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// printf("%d\n", fd_1);
		if (fd_1 == -1)
		{
			printf("%s\n", strerror(errno));
			exit(0);
		}
		all->redirect_1 = fd_1;
		skip_spaces(str, i);
	}
	else if (redirect == 1)
	{
		close(all->redirect_1);
		fd_1 = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_1 == -1)
		{
			printf("%s\n", strerror(errno));
			exit(0);
		}
		all->redirect_1 = fd_1;
		skip_spaces(str, i);
	}
	else
	{
		close(all->redirect_0);
		fd_2 = open(file_name, O_RDONLY);
		if (fd_2 == -1)
		{
			printf("%s\n", strerror(errno));
			exit(0);
		}
		all->redirect_0 = fd_2;
		// all->redir = file_name;
		skip_spaces(str, i);
	}

	freed(file_name);
}