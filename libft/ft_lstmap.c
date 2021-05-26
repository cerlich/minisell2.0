/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 06:38:54 by fgeorgan          #+#    #+#             */
/*   Updated: 2020/11/15 13:30:35 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*elem;

	if (lst)
	{
		if (!(head = (ft_lstnew(f(lst->content)))))
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			if (!(elem = (ft_lstnew(f(lst->content)))))
			{
				ft_lstclear(&head, del);
				return (head);
			}
			ft_lstadd_back(&head, elem);
			lst = lst->next;
		}
		return (head);
	}
	return (NULL);
}
