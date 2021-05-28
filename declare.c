#include "minishell.h"

static void	swap(char **env, int n, int tmp)
{
	char	*buf;

	buf = ft_strdup(env[n]);
	free(env[n]);
	env[n] = ft_strdup(env[tmp]);
	free(env[tmp]);
	env[tmp] = ft_strdup(buf);
	free(buf);
	buf = NULL;
}

static void	sort_env(char **env)
{
	int		i;
	int		n;
	int		min ;
	int		tmp;

	n = 0;
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
			swap(env, n, tmp);
		n++;
	}
}

void	print_declare(char **env)
{
	int	i;

	i = -1;
	sort_env(env);
	while (env[++i])
		printf("declare -x %.*s=\"%s\"\n",
			ft_strclen(env[i], '=') - 1, env[i],
			&env[i][ft_strclen(env[i], '=')]);
}
