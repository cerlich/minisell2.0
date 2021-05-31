#include "minishell.h"

static int	get_exit_code(t_all *all)
{
	int	n;

	n = -1;
	all->tmp = ft_atoi(all->args[1]);
	while (all->args[1][++n])
	{
		if (!ft_isdigit(all->args[1][n]) || all->tmp > 9223372036854775807)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				all->args[1]);
			all->pid->status_exit = 255;
			break ;
		}
	}
	if (all->tmp >= 0 && all->tmp <= 255)
		all->pid->status_exit = all->tmp;
	if (all->tmp >= 256 && all->tmp <= 9223372036854775807)
		all->pid->status_exit = all->tmp % 256;
	printf("exit\n");
	exit(all->pid->status_exit);
}

void	treat_exit(t_all *all)
{
	int	len;

	len = 0;
	while (all->args[len])
		len++;
	if (len == 1)
		exit(all->pid->status_exit);
	if (len > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (len == 2)
		get_exit_code(all);
}
