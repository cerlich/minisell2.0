/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:01:22 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/02/28 18:07:58 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_add(t_dlist **lst, t_dlist *new)
{
	t_dlist	*cur;

	if (lst && new)
	{
		cur = (*lst);
		if (!cur)
			*lst = new;
		else if (cur->next == NULL && cur->previous == NULL)
		{
			cur->next = new;
			cur->previous = new;
			new->next = *lst;
			new->previous = *lst;
		}
		else
		{
			cur = cur->previous;
			cur->next = new;
			new->next = *lst;
			new->previous = cur;
			(*lst)->previous = new;
		}
	}
}
