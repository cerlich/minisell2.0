#include "minishell.h"

void	relloc_args(char *string, t_all *all)
{
	int		i;
	char	**new_args;
	char	**old_args;
	char	***array;

	array = &all->args;
	i = 0;
	new_args = (char**)malloc(sizeof(char*) * (all->count_args + 2));
	// if (!new_args)
	// 	return ;
	while (i < all->count_args)
	{
		new_args[i] = ft_strdup((*array)[i]);
		// if (!new_args[i])
		// 	return ;
		i++;
	}
	new_args[i++] = ft_strdup(string);
	new_args[i] = NULL;
	old_args = *array;
	all->args = new_args;
	i = 0;
	d_freed(old_args);
	// while (old_args[i])
	// 	freed(old_args[i++]);
	// free(old_args);
	all->count_args++;
}

void	add_arg(t_all *all, char **string)
{
	relloc_args(*string, all);
	*string = ft_strdup("");
}