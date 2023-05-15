/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:35:24 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/15 13:34:54 by tde-melo         ###   ########.fr       */
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
		if (tokens->type != EMPTY)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}

int	check_state(int d, int s)
{
	if (d == 1 && s == -1)
		return (IN_DQUOTE);
	else if (d == -1 && s == 1)
		return (IN_QUOTE);
	else
		return (GENERAL);
}
