/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:13:26 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:01 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     lst: The address of a pointer to a node.
//     del: The address of the function used to delete
//     the content of the node.
// Return value
//     None
// External functs.
//     free
// Description
//     Deletes and frees the given node and every
//     successor of that node, using the function ’del’
//     and free(3).
//     Finally, the pointer to the list must be set to
//     NULL.

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			*lst = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = *lst;
		}
	}
}
