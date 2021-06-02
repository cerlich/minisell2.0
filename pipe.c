#include "minishell.h"

static void	to_exec_pipe(t_all *all, int **buf_fd, int i, char *cmd)
{
	if (i == 0)
	{
		close(buf_fd[i][0]);
		dup2(buf_fd[i][1], 1);
	}
	else if (i < all->count_pipes)
	{
		close(buf_fd[i - 1][1]);
		dup2(buf_fd[i - 1][0], 0);
		close(buf_fd[i][0]);
		dup2(buf_fd[i][1], 1);
	}
	else
	{
		close(buf_fd[i - 1][1]);
		dup2(buf_fd[i - 1][0], 0);
	}
	execve(cmd, all->pipes[i], all->envp);
}

static void	pipe_function(t_all *all, int **buf_fd, int i)
{
	char		**dirs;
	int			j;
	int			res;
	struct stat	buff;

	j = -1;
	dirs = ft_split(getenv("PATH"), ':');
	while (dirs[++j])
	{
		if (all->pipes[i][0][0] == '/' || (all->pipes[i][0][0] == '.' && \
			(all->pipes[i][0][1] == '/' || (all->pipes[i][0][1] == '.'
			&& all->pipes[i][0][2] == '/'))))
			dirs[j] = all->pipes[j][0];
		else
		{
			dirs[j] = relloc(dirs[j], '/');
			dirs[j] = ft_strjoin(dirs[j], all->pipes[i][0]);
		}
		res = stat(dirs[j], &buff);
		if (res == 0 && (buff.st_mode))
			to_exec_pipe(all, buf_fd, i, dirs[j]);
	}
	d_freed(dirs);
	printf("minishell: %s: command not found\n", all->pipes[i][0]);
}

static void	ft_pipe_p2(t_all *all, int **arr_fd, int *arr_pid, int *i)
{
	arr_pid[*i] = fork();
	if (arr_pid[*i] > 0 && *i != all->count_pipes)
		close(arr_fd[*i][1]);
	else if (arr_pid[*i] == 0)
		pipe_function(all, arr_fd, *i);
	(*i)++;
	dup2(all->fd[0], all->redirect_0);
	dup2(all->fd[1], all->redirect_1);
}

static int	**arr_of_fd_and_pids(int count_pipes, int **arr_pid)
{
	int	**arr_fd;
	int	i;

	arr_fd = (int **)malloc(sizeof(int *) * (count_pipes + 1));
	if (!arr_fd)
		return (NULL);
	i = -1;
	while (++i < count_pipes)
	{
		arr_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!arr_fd[i])
		{
			d_freed(arr_fd);
			return (NULL);
		}
		pipe(arr_fd[i]);
	}
	arr_fd[i] = 0;
	*arr_pid = (int *)malloc(sizeof(int) * (count_pipes + 1));
	if (!arr_pid)
	{
		d_freed(arr_fd);
		return (NULL);
	}
	return (arr_fd);
}

void	ft_pipe(t_all *all)
{
	int		**arr_fd;
	int		*arr_pid;
	int		j;
	int		i;

	j = -1;
	arr_fd = arr_of_fd_and_pids(all->count_pipes, &arr_pid);
	if (!arr_fd)
	{
		write(all->fd[1], ": malloc error\n", 15);
		return ;
	}
	i = 0;
	while (++j <= all->count_pipes)
		ft_pipe_p2(all, arr_fd, arr_pid, &i);
	while (--i >= 0)
		waitpid(arr_pid[i], &all->pid->status_exit, WUNTRACED);
	freed(arr_pid);
	d_freed(arr_fd);
	while (--all->num_of_pipes > -1 && all->pipes[all->num_of_pipes])
		d_freed(all->pipes[all->num_of_pipes]);
	all->num_of_pipes = 0;
}
