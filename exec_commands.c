#include "minishell.h"

static int	treat_utility(t_all *all, char *cmd)
{
	int			res;
	struct stat	buff;

	res = stat(cmd, &buff);
	if (res == 0 && buff.st_mode)
	{
		if (S_ISREG(buff.st_mode))
			to_exec(all, cmd, execve);
		else
			printf(": %s: is a directory\n", cmd);
		return (1);
	}
	return (0);
}

static void	treat_func_p2(t_all *all)
{
	if (!treat_utility(all, all->args[0]))
		printf("minishell>: %s: No such file or directory\n",
			all->args[0]);
}

void	treat_func(t_all *all)
{
	int			i;
	char		**dirs;

	i = -1;
	if (all->args[0][0] == '/' || (all->args[0][0] == '.' && (all->args[0][1] \
	== '/' || (all->args[0][1] == '.' && all->args[0][2] == '/'))))
	{
		treat_func_p2(all);
		return ;
	}
	dirs = ft_split(getenv("PATH"), ':');
	while (dirs[++i])
	{
		dirs[i] = relloc(dirs[i], '/');
		dirs[i] = ft_strjoin(dirs[i], all->args[0]);
		if (treat_utility(all, dirs[i]))
		{
			d_freed(dirs);
			return ;
		}
	}
	d_freed(dirs);
	printf("minishell>: %s: command not found\n", all->args[0]);
}

void	commands(t_all *all)
{
	if (!ft_strncmp(all->args[0], "echo", 5))
		treat_echo(all);
	else if (!ft_strncmp(all->args[0], "cd", 3))
		treat_cd(all);
	else if (!ft_strncmp(all->args[0], "export", 7))
		all->envp = treat_export(all);
	else if (!ft_strncmp(all->args[0], "unset", 6))
		all->envp = treat_unset(all);
	else if (!ft_strncmp(all->args[0], "env", 4))
		treat_env(all);
	else if (!ft_strncmp(all->args[0], "exit", 5))
		treat_exit(all);
	else if (!ft_strncmp(all->args[0], "pwd", 4))
		treat_pwd();
	else
		treat_func(all);
}
