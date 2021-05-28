#include "minishell.h"

void	treat_pwd(void)
{
	char	*dir;

	dir = ft_calloc(MAXPATHLEN, 1);
	getcwd(dir, MAXPATHLEN);
	printf("%s\n", dir);
	free (dir);
	dir = NULL;
}

void	treat_echo(t_all *all)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (!all->args[1])
	{
		ft_putchar_fd('\n', all->redirect_1);
		return ;
	}
	if (!ft_strncmp(all->args[1], "-n", 3))
		flag = 1;
	while (all->args[++i])
	{
		if (i == 1 && !ft_strncmp(all->args[i], "-n", 3))
			continue ;
		ft_putstr_fd(all->args[i], all->redirect_1);
		if (all->args[i + 1] != '\0')
			ft_putchar_fd(' ', all->redirect_1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', all->redirect_1);
}

static int	key(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] == '_' || ft_isalnum(str[i]))
	{
		n++;
		i++;
	}
	return (n);
}

char	*treat_dollar(char *str, int *j, t_all *all)
{
	char	*new;
	int		i;
	int		n;

	i = -1;
	n = key(&str[1]);
	*j += n;
	if (!ft_strncmp(&str[1], "?", 2))
	{
		new = ft_strdup(ft_itoa(all->pid->status_exit));
		*j += 1;
		return (new);
	}
	while (all->envp[++i])
	{
		if (!ft_strncmp(all->envp[i], &str[1], n) && all->envp[i][n] == '=')
		{
			new = ft_strdup(&all->envp[i][n + 1]);
			return (new);
		}
	}
	new = ft_strdup("");
	return (new);
}

void	treat_env(t_all *all)
{
	int	i;

	i = -1;
	if (!all->args[1])
	{
		while (all->envp[++i])
			printf("%s\n", all->envp[i]);
	}
	else
	{
		printf("env: %s: No such file or directory\n", all->args[1]);
		all->pid->status_exit = 1;
	}
}
