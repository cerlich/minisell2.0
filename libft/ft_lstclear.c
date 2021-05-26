/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 05:27:15 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/23 20:12:21 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*buff;

	if (lst)
	{
		tmp = *lst;
		while (tmp)
		{
			buff = tmp->next;
			ft_lstdelone(tmp, del);
			tmp = buff;
		}
		*lst = NULL;
	}
}
