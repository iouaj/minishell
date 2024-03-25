/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:24:46 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/07 12:15:18 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	(void) del;
	new_list = NULL;
	if (!lst->content)
		return (new_list);
	while (lst)
	{
		if (lst->content)
		{
			ft_lstadd_back(&new_list, ft_lstnew(f(lst->content)));
			if (!lst->content)
				del(lst->content);
		}
		lst = lst->next;
	}
	return (new_list);
}
