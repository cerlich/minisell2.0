/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/16 17:28:45 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s, char const *set)
{
	char	*fresh;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	ln;

	if (!s || !set)
		return (NULL);
	ln = ft_strlen(s);
	i = 0;
	j = 0;
	k = 0;
	if (!(ft_strncmp(s, "", 1)))
		return (ft_strdup(""));
	ln--;
	while (in_set(s[ln - j], set))
		j++;
	while (in_set(s[i], set))
		i++;
	if (i == (ln + 1) && j == (ln + 1))
		return (ft_strdup(""));
	fresh = ft_substr(s, i, (ln - j - i + 1));
	return (fresh);
}
