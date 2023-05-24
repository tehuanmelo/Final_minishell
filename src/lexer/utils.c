/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:35:24 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/24 17:13:19 by tde-melo         ###   ########.fr       */
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

t_elem	*get_list_prev_bound(t_elem *tokens)
{
	t_elem	*tmp_prev;

	tmp_prev = NULL;
	if (tokens->prev)
	{
		tmp_prev = tokens->prev;
		while (tmp_prev && (tmp_prev->type == WHITE_SPACE
				|| is_quote(tmp_prev->type) || tmp_prev->type == EMPTY))
			tmp_prev = tmp_prev->prev;
	}
	return (tmp_prev);
}

t_elem	*get_list_next_bound(t_elem *tokens)
{
	t_elem	*tmp_next;

	tmp_next = NULL;
	if (tokens->next)
	{
		tmp_next = tokens->next;
		while (tmp_next && (tmp_next->type == WHITE_SPACE
				|| is_quote(tmp_next->type) || tmp_next->type == EMPTY))
			tmp_next = tmp_next->next;
	}
	return (tmp_next);
}
