/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:05:39 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:26 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     lst: The beginning of the list.
// Return value
//     The length of the list
// External functs.
//     None
// Description
//     Counts the number of nodes in a list.

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*new;

	new = lst;
	i = 0;
	while (new)
	{
		i++;
		new = new->next;
	}
	return (i);
}

// int main()
// {
//     t_list *lst = NULL;
//     t_list *new = ft_lstnew("hello");
//     ft_lstadd_front(&lst, new);
//     t_list *new1 = ft_lstnew("world");
//     ft_lstadd_front(&lst, new1);
//     t_list *new2 = ft_lstnew("tehuen");
//     ft_lstadd_front(&lst, new2);

//     printf("%d\n", ft_lstsize(lst));
//     printf("%s\n", lst->next->content);

// }