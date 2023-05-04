/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:27:07 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/04 18:56:29 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	check_quotes(t_elem **tokens, enum e_type type)
{
	if (!(*tokens)->prev)
	{
		ft_putstr("minishel: command not found\n");
		return(EXIT_FAILURE);
	}
	*tokens = (*tokens)->next;
	while (*tokens)
	{
		if ((*tokens)->type == type)
			break ;
		*tokens = (*tokens)->next;
	}
	if (!*tokens)
	{
		ft_putstr("minishel: sintax error `unclosed quotes'\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_redir(t_elem *tokens)
{
	t_elem	*tmp_prev;
	t_elem	*tmp_next;

	tmp_prev = NULL;
	tmp_next = NULL;
	if (tokens->prev && tokens->next)
	{
		tmp_prev = tokens->prev;
		tmp_next = tokens->next;
		while (tmp_prev && (tmp_prev->type == WHITE_SPACE
				|| is_quote(tmp_prev->type) || tmp_prev->type == EMPTY))
			tmp_prev = tmp_prev->prev;
		while (tmp_next && (tmp_next->type == WHITE_SPACE
				|| is_quote(tmp_prev->type) || tmp_next->type == EMPTY))
			tmp_next = tmp_next->next;
	}
	if (tmp_next && tmp_prev)
	{
		if ((tmp_prev->type == WORD || tmp_prev->type == ENV)
			&& (tmp_next->type == WORD || tmp_next->type == ENV))
			return (EXIT_SUCCESS);
	}
	ft_putstr("minishel: sintax error near `redirection'\n");
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
		tmp_prev = tokens->prev;
		tmp_next = tokens->next;
		while (tmp_prev && (tmp_prev->type == WHITE_SPACE
				|| is_quote(tmp_prev->type) || tmp_prev->type == EMPTY))
			tmp_prev = tmp_prev->prev;
		while (tmp_next && (tmp_next->type == WHITE_SPACE
				|| is_quote(tmp_prev->type) || tmp_next->type == EMPTY))
			tmp_next = tmp_next->next;
	}
	if (tmp_next && tmp_prev)
	{
		if ((tmp_prev->type == WORD || tmp_prev->type == ENV)
			&& (tmp_next->type == WORD || tmp_next->type == ENV))
			return (EXIT_SUCCESS);
	}
	ft_putstr("minishel: sintax error near `pipe'\n");
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
