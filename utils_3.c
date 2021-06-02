#include "minishell.h"

void	relloc_args(char *string, t_all *all)
{
	int		i;
	char	**new_args;
	char	**old_args;
	char	***array;

	array = &all->args;
	i = 0;
	new_args = (char **)malloc(sizeof(char *) * (all->count_args + 2));
	while (i < all->count_args)
	{
		new_args[i] = ft_strdup((*array)[i]);
		i++;
	}
	new_args[i++] = ft_strdup(string);
	new_args[i] = NULL;
	old_args = *array;
	all->args = new_args;
	i = 0;
	d_freed(old_args);
	all->count_args++;
}

void	add_arg(t_all *all, char **string)
{
	relloc_args(*string, all);
	freed(*string);
	*string = ft_strdup("");
}

int	err_preparser(char *str, char *s)
{
	printf("minishell: %s\n", s);
	freed(str);
	return (1);
}

int	not_spec(char c)
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

int	check_redirect(char *str, int *i)
{
	if (str[*i] == '<')
		return (2);
	if (str[(*i) + 1] == '>')
	{
		(*i)++;
		return (1);
	}
	return (0);
}
