#include "minishell.h"

int	parse_args(char *str, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		if (!(ft_strchr(str, '=')))
			return (0);
		if (str[0] == '=')
			return (0);
	}
	if (ft_isdigit(str[0]))
		return (0);
	while (str[++i])
	{
		if (str[i] == '=' && flag == 1)
			break ;
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
	}
	return (1);
}

static int	check_args(t_all *all)
{
	int	len;
	int	i;
	int	n;

	len = 0;
	i = 0;
	while (all->args[++i])
	{
		if (!parse_args(all->args[i], 0))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				all->args[i]);
			all->pid->status_exit = 1;
			continue ;
		}
		n = -1;
		while (all->envp[++n])
		{
			if (!ft_strncmp(all->envp[n], all->args[i], ft_strlen(all->args[i]))
				&& all->envp[n][ft_strlen(all->args[i])] == '=')
				len++;
		}
	}
	return (len);
}

static void	rewrite_env(t_all *all, char **new_env, int len)
{
	int	i;
	int	n;
	int	flag;

	n = -1;
	while (all->envp[++n])
	{
		i = -1;
		flag = 0;
		while (all->args[++i])
		{
			if (!ft_strncmp(all->envp[n], all->args[i], ft_strlen(all->args[i]))
				&& all->envp[n][ft_strlen(all->args[i])] == '=')
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 0)
		{
			new_env[len] = ft_strdup(all->envp[n]);
			len++;
		}
	}
	d_freed(all->envp);
}

char	**treat_unset(t_all *all)
{
	char	**new_env;
	int		n;

	n = 0;
	while (all->envp[n])
		n++;
	new_env = (char **)ft_calloc(n - check_args(all) + 1, sizeof(char *));
	if (!new_env)
	{
		printf("minishell: malloc error\n");
		d_freed(all->envp);
		exit(1);
	}
	rewrite_env(all, new_env, 0);
	return (new_env);
}
