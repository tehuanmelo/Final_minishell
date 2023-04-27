/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:57:36 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:22:10 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstfree(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		tmp = tmp->next;
		free(list);
		list = tmp;
	}
}
