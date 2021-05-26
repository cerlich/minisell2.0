/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:57:30 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/10 03:37:26 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	n;
	void	*str;

	n = count * size;
	if (!(str = malloc(n)))
		return (NULL);
	ft_memset(str, 0, n);
	return (str);
}
