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
	int		status_exit;
}				t_pid;

typedef struct s_all
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
	int					semicolon;
	unsigned long long	tmp;
	t_pid				*pid;
}				t_all;

void	treat_echo(t_all *all);
void	treat_exit(t_all *all);
void	treat_pwd(void);
char	*treat_dollar(char *str, int *j, t_all *all);
void	treat_env(t_all *all);
int		treat_cd(t_all *all);
void	commands(t_all *all);
int		find_overlap(char **s1, char *s2);
int		parse_args(char *str, int flag);
char	**treat_export(t_all *all);
void	print_declare(char **env);
void	freed(void *content);
void	d_freed(void *content);
void	t_freed(void *content);
int		ft_strclen(const char *s, char c);
char	*relloc(char *str, char add);
char	*simple_quota(char *str, int *i);
void	dqouta_slash(char *str, int *i);
char	*double_quota(char *str, int *i, t_all *all);
void	skip_spaces(char *str, int *i);
char	**treat_unset(t_all *all);
void	relloc_args(char *string, t_all *all);
void	add_arg(t_all *all, char **string);
int		redirect(char *str, int *i, t_all *all);
int		red_while(char *str, int *i, char **file_name, t_all *all);
void	to_exec(t_all *all, char *cmd_path,
			int(*execve)(const char *, char *const *, char *const *));
void	ft_sigint(int sig);
void	ft_sigquit(int sig);
int		get_next_line(int fd, char **line);
void	execute(t_all *all);
int		parser(char *str, t_all *all);
void	parser_semicolon(t_all *all, char *str, char **string, int *i);
int		parser_pipe(t_all *all, char *str, char **string, int *i);
void	parser_s_quota(char **string, char *str, int *i);
void	parser_d_quota(t_all *all, char **string, char *str, int *i);
int		parser_redirect(t_all *all, char *str, char **string, int *i);
void	parser_dollar(t_all *all, char *str, char **string, int *i);
int		preparser(char *str, t_all *all);
int		err_preparser(char *str, char *s);
void	ft_pipe(t_all *all);
int		not_spec(char c);
int		check_redirect(char *str, int *i);

#endif