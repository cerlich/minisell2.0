/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:29:13 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/10 04:09:06 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*beg;

	if (lst && new)
	{
		beg = (*lst);
		if (!beg)
			*lst = new;
		else
		{
			while (beg->next)
				beg = beg->next;
			beg->next = new;
			new->next = NULL;
		}
	}
}
