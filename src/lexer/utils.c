/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:35:24 by tde-melo          #+#    #+#             */
/*   Updated: 2023/04/25 22:00:21 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	free_tokens_list(t_elem *tokens)
{
	t_elem	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp = tmp->next;
		if (tokens->type != ENV && tokens->type != EMPTY)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}
