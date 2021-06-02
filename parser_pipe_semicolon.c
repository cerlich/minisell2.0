#include "minishell.h"

static void	parser_utility_1(t_all *all)
{
	int	i;

	i = 0;
	if (!all->num_of_pipes)
		d_freed(all->args);
	if (all->num_of_pipes)
	{
		all->pipes[all->count_pipes++] = all->args;
	}
	all->args = (char **)malloc(sizeof(char *));
	all->args[0] = NULL;
	all->count_args = 0;
}

static void	parser_utility_2(t_all *all)
{
	int	i;

	i = 0;
	if (!all->count_pipes)
		d_freed(all->args);
	if (all->num_of_pipes)
	{
		all->pipes[all->count_pipes++] = all->args;
	}
	all->args = (char **)malloc(sizeof(char *));
	all->args[0] = NULL;
	all->count_args = 0;
}

void	parser_semicolon(t_all *all, char *str, char **string, int *i)
{
	if (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\t'
		&& ft_strncmp(*string, "", 1))
		add_arg(all, string);
	if (all->count_pipes)
	{
		all->semicolon = 1;
		all->pipes[all->count_pipes] = all->args;
		if (all->pipes[all->count_pipes][0] &&
			ft_strncmp(all->pipes[all->count_pipes][0], "", 1))
			execute(all);
		all->count_pipes = 0;
	}
	else
		execute(all);
	parser_utility_2(all);
	skip_spaces(str, i);
}

int	parser_pipe(t_all *all, char *str, char **string, int *i)
{
	if (str[(*i) + 1] == '|')
		return (1);
	if (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\t'
		&& ft_strncmp(*string, "", 1))
		add_arg(all, string);
	parser_utility_1(all);
	skip_spaces(str, i);
	return (0);
}
