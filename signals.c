#include "minishell.h"

t_pid	g_pid;

void	to_exec(t_all *all, char *cmd_path,
	int(*execve)(const char *, char *const *, char *const *))
{
	g_pid.pid = fork();
	dup2(all->redirect_1, 1);
	dup2(all->redirect_0, 0);
	if (g_pid.pid == 0)
		execve(cmd_path, all->args, all->envp);
	else
	{
		wait(&all->pid->status_exit);
		if (g_pid.status_exit == 131)
			all->pid->status_exit = 131;
		if (g_pid.status_exit == 130)
			all->pid->status_exit = 130;
	}
	dup2(all->fd[0], all->redirect_0);
	dup2(all->fd[1], all->redirect_1);
}

void	ft_sigint(int sig)
{
	if (g_pid.pid == 0)
	{
		ft_putstr_fd(" \b\b \b\b \b\b", 1);
		printf("\n");
		ft_putstr_fd("minishell>", 1);
	}
	else
	{
		printf("\n");
		kill(g_pid.pid, sig);
		g_pid.status_exit = 130;
		g_pid.pid = 0;
	}
}

void	ft_sigquit(int sig)
{
	if (g_pid.pid != 0)
	{
		kill(g_pid.pid, 3);
		g_pid.status_exit = 131;
		printf("Quit: %d\n", sig);
		g_pid.pid = 0;
	}
	if (g_pid.pid == 0)
	{
		ft_putstr_fd("\b \b\b \b", 1);
	}
}
