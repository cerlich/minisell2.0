#include "minishell.h"

char	**treat_unset(t_all *all)
{
    char **new_env;
    int i = 0;
    int n = -1;
    int len = 0;
    int flag = 0;

    while (all->args[++i])
    {
         if (!parse_args(all->args[i], all->envp, 0))
        {
            printf("minishell: unset: `%s': not a valid identifier\n", all->args[i]);
            //all->pid->status_exit = 1;
            continue ;
        }
        n = -1;
        while (all->envp[++n])
        {
            if (!ft_strncmp(all->envp[n], all->args[i], ft_strlen(all->args[i])) &&
                all->envp[n][ft_strlen(all->args[i])] == '=')
                    len++;
        } 
    }
    n = 0;
    while (all->envp[n])
        n++;
    new_env = (char **)ft_calloc(n - len + 1, sizeof(char *));
    if (!new_env)
    {
        printf("minishell: malloc error\n");
        d_freed(all->envp);
        //d_freed(all->args);
        exit(1);
    }
    n = -1;
    len = 0;
    while(all->envp[++n])
    {
        i = -1;
        flag = 0;
        while (all->args[++i])
        {
           if (!ft_strncmp(all->envp[n], all->args[i], ft_strlen(all->args[i])) &&
                all->envp[n][ft_strlen(all->args[i])] == '=')
           {
                flag = 1;
                break ;
           }
        }
        if (flag == 0)
        {
            new_env[len] = ft_strdup(all->envp[n]);
            len++;
        }
    }
    d_freed(all->envp);
    return (new_env);
}