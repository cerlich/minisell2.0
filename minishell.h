#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# include <signal.h>

typedef struct s_pid
{
	pid_t	pid;
	int 	status_exit;
	int fork;
}				t_pid;

typedef struct	s_all
{
	char				**envp;
	char				**args;
	char				***pipes;
	int					redirect_1;
	int					redirect_0;
	int					fd[2];
	int					count_pipes;
	int					count_args;
	int					num_of_pipes;
	unsigned long long	tmp;
	t_pid				*pid;
	//int					status_exit;
}				t_all;

void	treat_echo(t_all *all);
void	treat_pwd(void);
char	*treat_dollar(char *str, int *j, t_all *all);
void	treat_env(t_all *all);
int		treat_cd(t_all *all);
int		find_overlap(char **s1, char *s2);
int		parse_args(char *str, char **env, int flag);
char	**treat_export(t_all *all);
void	freed(char *str);
void	d_freed(char **str);
void	t_freed(char ***str);
int		ft_strclen(const char *s, char c);
char	*relloc(char *str, char add);
char	*simple_quota(char *str, int *i);
void	dqouta_slash(char *str, int *i);
char	*double_quota(char *str, int *i, t_all *all);
void	skip_spaces(char *str, int *i);
char	**treat_unset(t_all *all);
int		not_spec(char c);
void	relloc_args(char *string, t_all *all);
void	add_arg(t_all *all, char **string);
void	redirect_err(char *file_name, char *str, int *i);
int		check_redirect(char *str, int *i);
void	redirect(char *str, int *i, t_all *all);


#endif