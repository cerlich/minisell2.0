#include "minishell.h"

static int	preparser_p1(int *string_symbols, char *str, int *i)
{
	if (!(*string_symbols))
	{
		if (str[(*i) - 1] == '|' && str[(*i) + 1] == '|'
			&& str[(*i) + 2] == '|')
			return (err_preparser(str,
					"syntax error near unexpected token `||'"));
		else if (str[(*i) - 1] == '|' && str[(*i) + 1] == '|'
			&& str[(*i) + 2] != '|')
			return (err_preparser(str,
					"minishell: syntax error near unexpected token `|'"));
		else if (str[(*i) - 1] != '|')
			return (err_preparser(str,
					"syntax error near unexpected token `|'"));
	}
	*string_symbols = 0;
	return (0);
}

static int	preparser_p2(int *string_symbols, char *str, int *i)
{
	if (!(*string_symbols))
	{
		if (str[(*i) - 1] == ';' || str[(*i) + 1] == ';')
			return (err_preparser(str,
					"syntax error near unexpected token `;;'"));
		else
			return (err_preparser(str,
					"syntax error near unexpected token `;'"));
	}
	*string_symbols = 0;
	return (0);
}

static int	preparser_p3(char *str, int *i, int d_quotas, int s_quotas)
{
	if (str[*i] == '\\')
		return (err_preparser(str, "unclosed slash"));
	if (str[*i] == '|')
		return (err_preparser(str, "unclosed pipe"));
	if (d_quotas % 2 || s_quotas % 2)
		return (err_preparser(str, "unclosed quotation marks"));
	return (0);
}

static int	preparser_while(char *str, int *i, t_all *all, int quotas[2])
{
	int	string_symbols;

	string_symbols = 0;
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
			(quotas[1])++;
		else if (str[*i] == '\'')
			(quotas[0])++;
		else if (str[*i] == '|')
		{
			if (preparser_p1(&string_symbols, str, i))
				return (1);
			all->num_of_pipes++;
		}
		else if (str[*i] == ';' && (quotas[1] % 2 == 0 || quotas[0] % 2 == 0))
		{
			if (preparser_p2(&string_symbols, str, i))
				return (1);
		}
		else if (str[*i] != ' ' && str[*i] != '\t')
			string_symbols++;
	}
	return (0);
}

int	preparser(char *str, t_all *all)
{
	int	i;
	int	quotas[2];

	i = -1;
	quotas[0] = 0;
	quotas[1] = 0;
	skip_spaces(str, &i);
	if (preparser_while(str, &i, all, quotas))
		return (1);
	i--;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (preparser_p3(str, &i, quotas[1], quotas[0]))
		return (1);
	return (0);
}
