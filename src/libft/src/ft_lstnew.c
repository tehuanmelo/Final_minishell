/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:47:46 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:03:20 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parameters content:
**     The content to create the node with.
** Return value
**     The new node
** External functs.
**     malloc
** Description
**     Allocates (with malloc(3)) and returns a new node.
**     The member variable ’content’ is initialized with
**     the value of the parameter ’content’. The variable
**     ’next’ is initialized to NULL.
*/

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n;

	n = malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}

// int main()
// {
//     char *str = "hello";
//     t_list *new = ft_lstnew(str);

//         printf("%s\n", (char*)new->next);

// }