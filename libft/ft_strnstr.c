/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/16 17:06:30 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t n)
{
	size_t	i;
	size_t	ln;

	if (*substr == '\0')
		return ((char*)(str));
	i = 0;
	ln = ft_strlen(substr);
	while (*str != '\0')
	{
		if (i + ln > n)
			return (NULL);
		if (ft_strncmp(str, substr, ln) == 0)
			return ((char*)(str));
		str++;
		i++;
	}
	return (NULL);
}
