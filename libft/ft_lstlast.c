/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:58:34 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/12 02:45:47 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_next(t_list *lst)
{
	if (!lst)
		return (0);
	return (lst->next);
}

t_list			*ft_lstlast(t_list *lst)
{
	int c;

	c = ft_lstsize(lst);
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	while (--c)
	{
		lst = get_next(lst);
	}
	return (lst);
}
