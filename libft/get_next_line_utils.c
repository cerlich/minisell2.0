/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:45:33 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/05/04 15:02:09 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	count;

// 	count = 0;
// 	if (s)
// 	{
// 		while (s[count])
// 			count++;
// 		return (count);
// 	}
// 	return (0);
// }

char	*get_put(char *src)
{
	char	*nstr;
	int		j;
	int		i;

	i = 0;
	while (src[i] != '\n' && src[i])
		i++;
	if (!src[i])
	{
		free(src);
		return (NULL);
	}
	nstr = (char *)malloc(sizeof(char) * ((ft_strlen(src) - i) + 1));
	i++;
	j = 0;
	while (src[i])
	{
		nstr[j] = src[i];
		i++;
		j++;
	}
	nstr[j] = '\0';
	free(src);
	return (nstr);
}

char	*ft_add(char *s1, char *s2)
{
	char	*fresh;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	fresh = (char *)malloc((ft_strlen(s1) +
	ft_strlen(s2) + 1) * sizeof(*fresh));
	if (!(fresh))
		return (NULL);
	if (s1)
		while (s1[i])
			fresh[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			fresh[j++] = s2[i++];
	fresh[j] = '\0';
	free(s1);
	return (fresh);
}

char	*get_line(char *str)
{
	char	*nstr;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(nstr = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
