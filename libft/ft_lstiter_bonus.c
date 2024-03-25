/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:08:12 by iouajjou          #+#    #+#             */
/*   Updated: 2023/11/06 17:08:12 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*#include <stdio.h>

int main()
{
    t_list *list1 = ft_lstnew("premier");
    t_list *list2 = ft_lstnew("deux");
    t_list *list3 = ft_lstnew("trois");
    t_list *list4 = ft_lstnew("quatre");

    ft_lstadd_back(&list4, list3);
    ft_lstadd_back(&list3, list2);
    ft_lstadd_back(&list2, list1);
    //list4->list3->list2->list1
}*/
