#include "minishell.h"

void	execute(t_all *all)
{
	if (all->count_pipes)
	{
		ft_pipe(all);
	}
	else
	{
		commands(all);
	}
}

void	copy_env(t_all *all, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	all->envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		all->envp[i] = ft_strdup(env[i]);
	all->tmp = 0;
}

void	all_init(t_all *all)
{
	int	i;

	i = 0;
	all->args = (char **)malloc(sizeof(char *) * 1);
	all->args[0] = NULL;
	all->redirect_0 = 0;
	all->redirect_1 = 1;
	all->fd[0] = dup(0);
	all->fd[1] = dup(1);
	all->count_pipes = 0;
	all->tmp = 0;
	all->semicolon = 0;
}

static int	minishell(t_all *all)
{
	char	*line;

	ft_putstr_fd("minishell> ", 1);
	get_next_line(0, &line);
	if (preparser(line, all))
		return (1);
	all_init(all);
	if (parser(line, all))
	{
		free(line);
		return (1);
	}
	if (all->args[0] && ft_strncmp(all->args[0], "", 1))
		execute(all);
	else
	{
		dup2(all->fd[0], all->redirect_0);
		dup2(all->fd[1], all->redirect_1);
	}
	d_freed(all->args);
	free(line);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_all			all;
	static t_pid	ret;

	(void)argc;
	(void)argv;
	ret.status_exit = 0;
	all.pid = &ret;
	copy_env(&all, env);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		if (minishell(&all))
			continue ;
	}
	return (0);
}
