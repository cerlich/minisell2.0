/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/10 03:21:03 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int ch)
{
	char	*str;
	size_t	ln;

	str = (char*)s;
	ln = ft_strlen(s);
	if (ch == '\0')
		return (str + ln);
	while (ln > 0)
	{
		ln--;
		if (str[ln] == ch)
			return (str + ln);
	}
	return (NULL);
}
