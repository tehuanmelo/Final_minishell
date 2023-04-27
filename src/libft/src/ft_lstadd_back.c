/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 09:59:06 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:02:55 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parameters
**     lst: The address of a pointer to the first link of
**     a list.
**     new: The address of a pointer to the node to be
**     added to the list.
** Return value
**     None
** External functs.
**     None
** Description
**     Adds the node ’new’ at the end of the list.
*/

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!(lst || new))
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

// int main()
// {

//     t_list *lst = NULL;

//     ft_lstadd_back(&lst, ft_lstnew("world"));
//     ft_lstadd_front(&lst, ft_lstnew("hello"));

//     printf("%s\n", (char*)lst->next->content);
// }