/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:03:08 by fgeorgan          #+#    #+#             */
/*   Updated: 2021/02/28 18:03:29 by fgeorgan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_new(void *content)
{
	t_dlist	*new;

	if (!(new = malloc(sizeof(t_dlist))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}
