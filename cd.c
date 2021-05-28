#include "minishell.h"

static void	change_pwd(char *old, char *new, t_all *all)
{
	int	i;

	i = -1;
	while (all->envp[++i])
	{
		if (!ft_strncmp(all->envp[i], "PWD", 3))
		{
			free(all->envp[i]);
			all->envp[i] = ft_strjoin(ft_strdup("PWD="), new);
			free(new);
			new = NULL;
		}
		if (!ft_strncmp(all->envp[i], "OLDPWD", 6))
		{
			free(all->envp[i]);
			all->envp[i] = ft_strjoin(ft_strdup("OLDPWD="), old);
			free(old);
			old = NULL;
		}
	}
}

static void	cd_home(t_all *all, char *new)
{
	int	i;

	i = 0;
	new = treat_dollar("$USER", &i, all);
	free(all->args[0]);
	all->args[0] = ft_strjoin(ft_strdup("/Users/"), new);
	if (chdir(all->args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", all->args[0]);
		all->pid->status_exit = 1;
	}
	free(new);
	new = NULL;
}

int	treat_cd(t_all *all)
{
	char	*old;
	char	*new;

	old = ft_calloc(MAXPATHLEN, 1);
	getcwd(old, MAXPATHLEN);
	if (!all->args[1])
		cd_home(all, new);
	else if (chdir(all->args[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", all->args[1]);
		free(old);
		old = NULL;
		all->pid->status_exit = 1;
		return (0);
	}
	new = ft_calloc(MAXPATHLEN, 1);
	getcwd(new, MAXPATHLEN);
	change_pwd(old, new, all);
	return (0);
}
