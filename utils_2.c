#include "minishell.h"

char	*relloc(char *str, char add)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !add)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return (str);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = add;
	new_str[i] = '\0';
	freed(str);
	str = NULL;
	return (new_str);
}

char	*simple_quota(char *str, int *i)
{
	int		j;
	char	*substr;

	j = 0;
	while (str[++(*i)] != '\'')
		j++;
	substr = ft_substr(str, *i - j, j);
	return (substr);
}

void	dqouta_slash(char *str, int *i)
{
	if (str[*i + 1] == '$' || str[*i + 1] == '\"' || str[*i + 1] == '\\')
		(*i)++;
}

char	*double_quota(char *str, int *i, t_all *all)
{
	char	*substr;

	substr = ft_strdup("");
	while (str[++(*i)] != '\"')
	{
		if (str[(*i)] == '\\')
			dqouta_slash(str, i);
		else if (str[(*i)] == '$')
		{
			if (ft_isalpha(str[(*i) + 1]))
			{
				freed(substr);
				substr = treat_dollar(&str[*i], i, all);
			}
			else
				substr = relloc(substr, str[*i]);
		}
		else
			substr = relloc(substr, str[*i]);
	}
	return (substr);
}

void	skip_spaces(char *str, int *i)
{
	(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	(*i)--;
}
