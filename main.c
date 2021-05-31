#include "minishell.h"

static int	treat_utility(t_all *all, char *cmd)
{
	int		res;
	struct stat	buff;

	res = stat(cmd, &buff);
	if (res == 0 && (buff.st_mode))
	{
		to_exec(all, cmd, execve);
		return (1);
	}
	return (0);
}

void	treat_func(t_all *all)
{
	int		i;
	int		res;
	char	**dirs;
	struct stat	buff;
	char *tmp;
	// char	*shel_lvl[3];

	i = -1;
	if (all->args[0][0] == '/' || (all->args[0][0] == '.' && \
	(all->args[0][1] == '/' || (all->args[0][1] == '.' && all->args[0][2] == '/'))))
	{
		// if (!ft_strncmp(all->args[0], "./a.out", 8))
		// {
		// 	shel_lvl[0] = "env";
		// 	shel_lvl[1] = "SHLVL=2";
		// 	shel_lvl[2] = NULL;
		// 	all->envp = treat_export(all->envp, shel_lvl);
		// }
		if (!treat_utility(all, all->args[0]))
			printf("minishell>: %s: No such file or directory\n", all->args[0]);
		return ;
	}
	//dirs = ft_split(getenv("PATH"), ':');
	tmp = treat_dollar("$PATH", &i, all);
	dirs = ft_split(tmp, ':');
	free(tmp);
	i = -1;
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
	// if (!all->args)
	// 	func;
	if (!ft_strncmp(all->args[0], "echo", 5))
		treat_echo(all);
	else if(!ft_strncmp(all->args[0], "cd", 3))
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
	// else if (!ft_strncmp(all->args[0], "bash", 5))
	// 	trat_bash();
	// else if (!ft_strncmp(all->args[0], "", 1))
	// 	write(1, "", 1);
	else
		treat_func(all);
}

void	to_exec_pipe(t_all *all, int **buf_fd, int i, char *cmd)
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
	// dup2(all->fd[0], all->redirect_0);
	// dup2(all->fd[1], all->redirect_1);
	// if (all->redirect_0 != 0)
		// dup2(all->redirect_0, all->fd[0]);
	// if (all->redirect_1 != 1)
		// dup2(all->redirect_1, all->fd[1]);
	
	execve(cmd, all->pipes[i], all->envp);
}

void	pipe_function(t_all *all, int **buf_fd, int i)
{
	char	**dirs;
	int		j;
	int		res;
	struct stat	buff;

	j = -1;
	dirs = ft_split(getenv("PATH"), ':');
	while (dirs[++j])
	{
		if (all->pipes[i][0][0] == '/' || (all->pipes[i][0][0] == '.' && \
		(all->pipes[i][0][1] == '/' || (all->pipes[i][0][1] == '.' && all->pipes[i][0][2] == '/'))))
			dirs[j] = all->pipes[j][0];
		else
		{
			dirs[j] = relloc(dirs[j], '/');
			dirs[j] = ft_strjoin(dirs[j], all->pipes[i][0]);
		}
		res = stat(dirs[j], &buff);
		if (res == 0 && (buff.st_mode))
			to_exec_pipe(all, buf_fd, i, dirs[j]);
		// else
		// 	break;
	}
	d_freed(dirs);
	printf("minishell: %s: command not found\n", all->pipes[i][0]);
}

int	**arr_of_fd_and_pids(int count_pipes, int **arr_pid)
{
	int **arr_fd;
	int i;
	arr_fd = (int **)malloc(sizeof(int *) * count_pipes);
	if (!arr_fd)
		return (NULL);
	i = -1;
	while (++i < count_pipes)
	{
		arr_fd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(arr_fd[i]);
	}
	*arr_pid = (int *)malloc(sizeof(int) * (count_pipes + 1));
	return (arr_fd);
}

void	ft_pipe(t_all *all)
{
	int		**arr_fd;
	int		*arr_pid;
	int		j;
	int		i;

	j = 0;
	arr_fd = arr_of_fd_and_pids(all->count_pipes, &arr_pid);
	i = 0;
	while (j <= all->count_pipes)
	{
		arr_pid[i] = fork();
		if (arr_pid[i] > 0 && i != all->count_pipes)
			close(arr_fd[i][1]);
		else if (arr_pid[i] == 0)
		{
			pipe_function(all, arr_fd, i);
			exit (0);
		}
		i++;
		j++;
	}
	while (--i >= 0)
		waitpid(arr_pid[i], &all->pid->status_exit, WUNTRACED);
}

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
	dup2(all->fd[0], all->redirect_0);
	dup2(all->fd[1], all->redirect_1);
}

void copy_env(t_all *all, char **env)
{
	int i = 0;
	while (env[i])
		i++;
	all->envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		all->envp[i] = ft_strdup(env[i]);
}

void    all_init(t_all *all, char **env)
{
	int i = 0;
	all->args = (char**)malloc(sizeof(char*) * 1);
	// while(all->args[i])
	// 	all->args[i++] = NULL;
	all->args[0] = NULL;
	all->redirect_0 = 0;
	all->redirect_1 = 1;
	all->fd[0] = dup(0);
	all->fd[1] = dup(1);
	all->count_pipes = 0;
	//copy_env(all, env);
	// all->pipes = (char***)malloc(sizeof(char**) * all->num_of_pipes);
	// while (all->pipes[i])
	// 	all->pipes[i++] = NULL;
	all->tmp = 0;
	// all->pid->status_exit = 0;
}

void	parser_utility(t_all *all)
{
	int	i;

	i = 0;
	if (all->num_of_pipes)
		all->pipes[all->count_pipes++] = all->args;
	// d_freed(all->args);
	// while (all->args[i])
	// 	free(all->args[i++]);
	// free(all->args);
	// all->args = NULL;
	all->args = (char**)malloc(sizeof(char*));
	all->args[0] = NULL;
	all->count_args = 0;
	// if (all->count_pipes == 1)
	// 	all->count_pipes = 0;
	// all_init(all, all->envp);
}

int	parser(char *str, t_all *all)
{
	int		i;
	char	*string;
	char	*tmp;

	i = -1;
	all->count_args = 0;
	string = ft_strdup("");
	skip_spaces(str, &i);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			tmp = simple_quota(str, &i);
			string = ft_strjoin(string, tmp);
			freed(tmp);
		}
		else if (str[i] == '\"')
		{
			tmp = double_quota(str, &i, all);
			string = ft_strjoin(string, tmp);
			freed(tmp);
		}
		else if (str[i] == '\\')
			string = relloc(string, str[++i]);
		else if (str[i] == '>' || str[i] == '<')
        {
            if (str[i - 1] != ' ' && str[i - 1] != '\t')
                add_arg(all, &string);
            if (redirect(str, &i, all))
                return (1);
            skip_spaces(str, &i);
            i--;
        }
		else if ((str[i] == ' ' || str[i] == '\t'))
		{
			if (ft_strncmp(string, "", 1))
				add_arg(all, &string);
			skip_spaces(str, &i);
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				break;
			if (str[i - 1] != ' ' && str[i - 1] != '\t')
				add_arg(all, &string);
			parser_utility(all);
			skip_spaces(str, &i);
		}
		else if (str[i] == ';')
		{
			if (str[i - 1] != ' ' && str[i - 1] != '\t' && ft_strncmp(string, "", 1))
				add_arg(all, &string);
			// skip_spaces(str, &i);
			// freed(string);
			if (all->count_pipes)
			{
				all->pipes[all->count_pipes] = all->args;
				if (all->pipes[all->count_pipes][0] && ft_strncmp(all->pipes[all->count_pipes][0], "", 1))
					execute(all);
			}
			else
				execute(all);
			parser_utility(all);
			skip_spaces(str, &i);
			// d_freed(all->args);
		}
		else if (str[i] == '$')
		{
			if (ft_isalpha(str[i + 1]))
				tmp = treat_dollar(&str[i], &i, all);
			else if (str[i + 1] == '?')
				tmp = treat_dollar(&str[i], &i, all);
			else
				tmp = relloc(ft_strdup(""), str[i]);
			string = ft_strjoin(string, tmp);
			freed(tmp);
			// string = treat_dollar(&str[i], &i, all->envp);
			// add_arg(all, &string);
		}
		else
			string = relloc(string, str[i]);;
	}
	if (i > ft_strlen(str))
		i = ft_strlen(str) + 1;
	if (ft_strncmp(string, "", 1) && ((str[--i] && (str[i] != ' ' && str[i] != '\t')) || str[i] == '\'' || str[i] == '\"'))
		relloc_args(string, all);
	if (all->count_pipes)
		all->pipes[all->count_pipes] = all->args;
	freed(string);
	return (0);
}

int	err_preparser(char *str, char *s)
{
	printf("minishell: %s\n", s);
	freed(str);
	return (1);
}

int	preparser(char *str, t_all *all)
{
	int     i;
	int     s_quotas;
	int     d_quotas;
	int     string_symbols;
	i = -1;
	d_quotas = 0;
	s_quotas = 0;
	string_symbols = 0;
	skip_spaces(str, &i);
	while (str[++i])
	{
		if (str[i] == '\"')
			d_quotas++;
		else if (str[i] == '\'')
			s_quotas++;
		else if (str[i] == '|')
		{
			if (!string_symbols)
			{
				if (str[i - 1] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
					return (err_preparser(str, "syntax error near unexpected token `||'"));
				else if (str[i - 1] == '|' && str[i + 1] == '|' && str[i + 2] != '|')
					return (err_preparser(str, "minishell: syntax error near unexpected token `|'"));
				else if (str[i - 1] != '|')
					return (err_preparser(str, "syntax error near unexpected token `|'"));
			}
			all->num_of_pipes++;
			string_symbols = 0;
		}
		else if (str[i] == ';' && (d_quotas % 2 == 0 || s_quotas % 2 == 0))
		{
			if (!string_symbols)
			{
				if (str[i - 1] == ';' || str[i + 1] == ';')
					return (err_preparser(str, "syntax error near unexpected token `;;'"));
				else
					return (err_preparser(str, "syntax error near unexpected token `;'"));
			}
			string_symbols = 0;
		}
		else if (str[i] != ' ' && str[i] != '\t')
			string_symbols++;
	}
	i--;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '\\')
		return (err_preparser(str, "unclosed slash"));
	if (str[i] == '|')
		return (err_preparser(str, "unclosed pipe"));
	if (d_quotas % 2 || s_quotas % 2)
		return (err_preparser(str, "unclosed quotation marks"));
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_all	all;
	int		status;
	static t_pid	ret;

	// char *d = ft_strdup("pwd |cat -n|grep 1");
	// int c =-1;
	(void)argc;
	(void)argv;
	all.tmp = 0;
	ret.status_exit = 0;
	all.pid = &ret;
	copy_env(&all, env);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		ft_putstr_fd("minishell> ", 1);
		get_next_line(0, &line);
		if (preparser(line, &all))
			continue;
		all_init(&all, env);
		// printf("|%s|\n", all.args[0]);
		// printf("|%s|\n", all.args[1]);
		// printf("|%s|\n", all.args[2]);
		if (parser(line, &all))
			continue;
		if (all.args[0] && ft_strncmp(all.args[0], "", 1))
			execute(&all);
		// printf("|%s|\n", all.args[0]);
		// printf("|%s|\n", all.args[1]);
		// printf("|%s|\n", all.args[2]);
		d_freed(all.args);
		// t_freed(all.pipes);
		free(line);
	}
	free(line);
	return 0;
}

// ls>1>2		ls -a |'ca't -n|grep 5		ls	 | cat -n ; ls -a | grep main		ls -a |'ca't -n| grep 5 ;  	pwd | cat -n
// Пустая строка
// Некорректно работает grep, при передаче редиректа вначале
// r = read(0, line, 100);
	// while (line[++i])
	// 	if (line[i] == '\n')
	// 	{
	// 		line[i] = '\0';
	// 		break;
	// 	}


// cd exit treat_func
