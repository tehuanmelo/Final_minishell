/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:35:05 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:06 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     lst: The address of a pointer to a node.
//     f: The address of the function used to iterate on
//     the list.
// Return value
//     None
// External functs.
//     None
// Description
//     Iterates the list ’lst’ and applies the function
//     ’f’ on the content of each node.

#include "../inc/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
