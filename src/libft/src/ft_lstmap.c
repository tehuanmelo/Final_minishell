/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:02:55 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:16 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     lst: The address of a pointer to a node.
//     f: The address of the function used to iterate on
//     the list.
//     del: The address of the function used to delete
//     the content of a node if needed.
// Return value
//     The new list.
//     NULL if the allocation fails.
// External functs.
//     malloc, free
// Description
//     Iterates the list ’lst’ and applies the function
//     ’f’ on the content of each node. Creates a new
//     list resulting of the successive applications of
//     the function ’f’. The ’del’ function is used to
//     delete the content of a node if needed.

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	if (!(lst))
		return (NULL);
	head = ft_lstnew(f(lst->content));
	tmp = head;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst->content));
		if (!(tmp->next))
			ft_lstclear(&head, del);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (head);
}
