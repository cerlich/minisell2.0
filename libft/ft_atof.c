/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:17:42 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/03/09 16:34:53 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	check_dot(const char *str, int i, float res)
{
	float	dot_res;

	if (str[i] != '.')
		return (res);
	i++;
	dot_res = (res < 0) ? -0.1 : 0.1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res += dot_res * (str[i++] - '0');
		dot_res *= 0.1;
	}
	return (res);
}

float	ft_atof(const char *str)
{
	size_t	i;
	int		is_neg;
	float	res;

	if (!str)
		return (0);
	i = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	is_neg = (str[i] == '-') ? -1 : 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	res = check_dot(str, i, res);
	return (res);
}
