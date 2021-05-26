#include "minishell.h"

int	parse_args(char *str, char **env, int flag)
{
    int i = -1;
    int n = -1;
    if (flag == 1)
    {
        if (!(ft_strchr(str, '=')))
            return (0);
        //if (find_overlap(env, str) >= 0)
        //   return (0);
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

static void sort_env(char **env)
{
	char	*buf;
	int		i = 0;
	int		n = 0;
	int		min ;
	int		tmp;

	while (env[n])
	{
	i = n + 1;
	tmp = -1;
	min = env[n][0];
	while (env[i])
	{
		if (env[i][0] < min)
		{
			min = env[i][0];
			tmp = i;
		}
		i++;
	}
	if (tmp > 0)
		{
			buf = ft_strdup(env[n]);
			free(env[n]);
			env[n] = ft_strdup(env[tmp]);
			free(env[tmp]);
			env[tmp] = ft_strdup(buf);
			free(buf);
			buf = NULL;
		}
		n++;
	}
}

static	void	print_declare(char **env)
{
	int i = -1;
	sort_env(env);
	
	while (env[++i])
		printf("declare -x %.*s=\"%s\"\n", ft_strclen(env[i], '=') - 1, env[i], 
			&env[i][ft_strclen(env[i], '=')]);
}

char	**treat_export(t_all *all)
{
	char **new_env;
	int i = 0;
	int n = 0;
	int len = 0;

	if (!all->args[1])
		print_declare(all->envp);
	while (all->envp[i])
		i++;
	while (all->args[++n])
	{
		if (!parse_args(all->args[n], all->envp, 1))
		{
			printf("minishell: export: `%s': not a valid identifier\n", all->args[n]);
			//all->pid->status_exit = 1;
			continue ;
		}
		len++;
	}
	new_env = (char **)ft_calloc(len + i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
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
		if (parse_args(all->args[len], all->envp, 1))
		{
			new_env[i] = ft_strdup(all->args[len]);
			i++;
		}
	}
	d_freed(all->envp);
	return (new_env);
}