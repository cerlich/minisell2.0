#include "minishell.h"

static void	rewrite_env(t_all *all, char **new_env)
{
	int	i;
	int	len;
	int	n;

	i = -1;
	while (all->envp[++i])
	{
		n = find_overlap(all->args, all->envp[i]);
		if (n >= 0)
			new_env[i] = ft_strdup(all->args[n]);
		else
			new_env[i] = ft_strdup(all->envp[i]);
	}
	len = -1;
	while (all->args[++len])
	{
		if (find_overlap(all->envp, all->args[len]) >= 0)
			continue ;
		if (parse_args(all->args[len], 1))
		{
			new_env[i] = ft_strdup(all->args[len]);
			i++;
		}
	}
	d_freed(all->envp);
}

static int	check_args(t_all *all)
{
	int	len;
	int	n;

	len = 0;
	n = 0;
	while (all->args[++n])
	{
		if (!parse_args(all->args[n], 1))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				all->args[n]);
			all->pid->status_exit = 1;
			continue ;
		}
		len++;
	}
	return (len);
}

char	**treat_export(t_all *all)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!all->args[1])
		print_declare(all->envp);
	while (all->envp[i])
		i++;
	new_env = (char **)ft_calloc(check_args(all) + i + 1, sizeof(char *));
	if (!new_env)
	{
		printf("minishell: malloc error\n");
		d_freed(all->envp);
		exit(1);
	}
	rewrite_env(all, new_env);
	return (new_env);
}
