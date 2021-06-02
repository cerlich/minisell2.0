#include "minishell.h"

static int	red_null(char **file_name, t_all *all)
{
	int	fd;

	close(all->redirect_1);
	fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		free(*file_name);
		return (1);
	}
	all->redirect_1 = fd;
	return (0);
}

static int	red_one(char **file_name, t_all *all)
{
	int	fd;

	close(all->redirect_1);
	fd = open(*file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		free(*file_name);
		return (1);
	}
	all->redirect_1 = fd;
	return (0);
}

static int	red_two(char **file_name, t_all *all)
{
	int	fd;

	close(all->redirect_0);
	fd = open(*file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		free(*file_name);
		return (1);
	}
	all->redirect_0 = fd;
	return (0);
}

static int	red_p2(char *str, char **file_name, int *i, t_all *all)
{
	skip_spaces(str, i);
	if (!str[(*i) + 1])
	{
		write(1,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		free(*file_name);
		return (1);
	}
	while (not_spec(str[++(*i)]))
	{
		if (red_while(str, i, file_name, all))
			return (1);
	}
	skip_spaces(str, i);
	return (0);
}

int	redirect(char *str, int *i, t_all *all)
{
	char	*file_name;
	int		redirect;

	file_name = ft_strdup("");
	redirect = check_redirect(str, i);
	if (red_p2(str, &file_name, i, all))
		return (1);
	if (redirect == 0)
	{
		if (red_null(&file_name, all))
			return (1);
	}
	else if (redirect == 1)
	{
		if (red_one(&file_name, all))
			return (1);
	}
	else
	{
		if (red_two(&file_name, all))
			return (1);
	}
	skip_spaces(str, i);
	freed(file_name);
	return (0);
}
