/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:27:07 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/24 17:48:49 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(t_elem **tokens, enum e_type type)
{
	*tokens = (*tokens)->next;
	while (*tokens)
	{
		if ((*tokens)->type == type)
			break ;
		*tokens = (*tokens)->next;
	}
	if (!*tokens)
	{
		g_data.exit_code = 127;
		ft_putstr("minishell: sintax error `unclosed quotes'\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_redir(t_elem *tokens)
{
	t_elem	*tmp_next;

	tmp_next = get_list_next_bound(tokens);
	if (tmp_next)
	{
		if ((tmp_next->type == WORD || tmp_next->type == ENV
				|| tmp_next->type == PIPE))
			return (EXIT_SUCCESS);
	}
	syntax_error_message(tokens->content);
	return (EXIT_FAILURE);
}

int	check_pipe(t_elem *tokens)
{
	t_elem	*tmp_prev;
	t_elem	*tmp_next;

	tmp_prev = NULL;
	tmp_next = NULL;
	if (tokens->prev && tokens->next)
	{
		tmp_prev = get_list_prev_bound(tokens);
		tmp_next = get_list_next_bound(tokens);
	}
	if (tmp_next && tmp_prev)
	{
		if ((tmp_prev->type == WORD || tmp_prev->type == ENV
				|| (is_redir(tmp_prev->type) && tmp_prev->next->type == PIPE))
			&& (tmp_next->type == WORD || tmp_next->type == ENV
				|| is_redir(tmp_next->type)))
			return (EXIT_SUCCESS);
	}
	syntax_error_message(tokens->content);
	return (EXIT_FAILURE);
}

int	sintax_error(t_data *data)
{
	t_elem	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (is_redir(tmp->type))
		{
			if (check_redir(tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (is_pipe(tmp->type))
		{
			if (check_pipe(tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (is_quote(tmp->type))
		{
			if (check_quotes(&tmp, tmp->type))
				return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
