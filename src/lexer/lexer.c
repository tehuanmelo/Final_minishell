/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:19 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/15 13:34:17 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

enum e_type	check_token(char *input, enum e_state state)
{
	if (ft_strcmp("|", input) == 0 && !is_in_quotes(state))
		return (PIPE);
	else if (ft_strcmp(">", input) == 0 && !is_in_quotes(state))
		return (REDIR_OUT);
	else if (ft_strcmp("<", input) == 0 && !is_in_quotes(state))
		return (REDIR_IN);
	else if (ft_strcmp(">>", input) == 0 && !is_in_quotes(state))
		return (DREDIR_OUT);
	else if (ft_strcmp("<<", input) == 0 && !is_in_quotes(state))
		return (HERE_DOC);
	else if (ft_strcmp(" ", input) == 0 && !is_in_quotes(state))
		return (WHITE_SPACE);
	else if (ft_strcmp("\"", input) == 0 && !is_in_quotes(state))
		return (D_QUOTE);
	else if (ft_strcmp("'", input) == 0 && !is_in_quotes(state))
		return (S_QUOTE);
	else if (*input == '$' && state != IN_QUOTE)
	{
		if (is_env(input))
			return (ENV);
		return (WORD);
	}
	return (WORD);
}

enum e_state	get_state(char *content, int d_quotes_flag, int s_quotes_flag)
{
	enum e_state	state;

	if ((d_quotes_flag == 1 && ft_strcmp("\"", content) == 0)
		|| (s_quotes_flag == 1 && ft_strcmp("'", content) == 0))
		state = GENERAL;
	else
		state = check_state(d_quotes_flag, s_quotes_flag);
	return (state);
}

t_elem	*init_new_element(void)
{
	t_elem	*new;

	new = malloc(sizeof(t_elem));
	if (!new)
		return (NULL);
	new->len = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	append_element(t_elem **list, t_elem *new_element)
{
	t_elem	*tmp;

	if (!*list)
		*list = new_element;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_element;
		new_element->prev = tmp;
	}
}

t_elem	*get_tokens_list(char *input)
{
	t_elem	*list;
	t_elem	*new;
	int		d_quotes_flag;
	int		s_quotes_flag;

	list = NULL;
	new = NULL;
	d_quotes_flag = -1;
	s_quotes_flag = -1;
	while (*input)
	{
		new = init_new_element();
		check_quotes_flag(*input, &d_quotes_flag, &s_quotes_flag);
		new->len = get_str_length(input);
		new->content = ft_substr(input, 0, new->len);
		new->state = get_state(new->content, d_quotes_flag, s_quotes_flag);
		new->type = check_token(new->content, new->state);
		append_element(&list, new);
		input += new->len;
	}
	return (list);
}
