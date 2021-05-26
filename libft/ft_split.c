/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/05/03 16:51:28 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**malloc_err(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static unsigned int	n_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static void			nxt_str(char **str, unsigned int *len,
					char c)
{
	unsigned int i;

	*str += *len;
	*len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char				**ft_split(char const *s, char c)
{
	char			**arr;
	char			*str;
	unsigned int	len;
	unsigned int	c_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	c_strs = n_strs(s, c);
	if (!(arr = malloc(sizeof(char *) * (c_strs + 1))))
		return (NULL);
	i = 0;
	str = (char *)s;
	len = 0;
	while (i < c_strs)
	{
		nxt_str(&str, &len, c);
		if (!(arr[i] = malloc((len + 1) * sizeof(char))))
			return (malloc_err(arr));
		ft_strlcpy(arr[i], str, len + 1);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
