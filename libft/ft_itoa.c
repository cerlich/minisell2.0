/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/10 06:24:20 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(int n)
{
	if (n / 10)
		return (nlen(n / 10) + 1);
	else
		return (1);
}

static size_t	sqr(size_t len)
{
	if (len == 1)
		return (10);
	else
		return (sqr(len - 1) * 10);
}

static char		elems(int n, size_t ln)
{
	if (ln != 0)
		n = n / sqr(ln);
	n %= 10;
	if (n == 0)
		return ('0');
	if (n == 1)
		return ('1');
	if (n == 2)
		return ('2');
	if (n == 3)
		return ('3');
	if (n == 4)
		return ('4');
	if (n == 5)
		return ('5');
	if (n == 6)
		return ('6');
	if (n == 7)
		return ('7');
	if (n == 8)
		return ('8');
	return ('9');
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	len = nlen(n);
	if (n < 0)
		str = (char*)malloc((len + 2) * sizeof(*str));
	else
		str = (char*)malloc((len + 1) * sizeof(*str));
	if (!(str))
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		n *= -1;
	}
	while (len)
		str[i++] = elems(n, --len);
	str[i] = '\0';
	return (str);
}
