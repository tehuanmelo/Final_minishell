/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:10:33 by tde-melo          #+#    #+#             */
/*   Updated: 2023/04/25 22:00:21 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	get_env_value(t_elem *tokens)
{
	char	*str;
	char	*content;

	content = tokens->content;
	if ((!ft_isalpha(*(++content)) && *content != '_'))
		tokens->type = WORD;
	else
	{
		str = getenv(content);
		if (str)
		{
			tokens->content = str;
			tokens->len = ft_strlen(str);
		}
		else
		{
			tokens->content = "";
			tokens->len = 0;
			tokens->type = EMPTY;
		}
	}
	free(--content);
}

void	check_here_doc_variable(t_data *data)
{
	t_elem	*head;
	t_elem	*tmp;

	head = data->tokens;
	tmp = NULL;
	while (head)
	{
		if (head->type == HERE_DOC)
		{
			tmp = head;
			if (tmp->next)
			{
				tmp = tmp->next;
				while (tmp && (tmp->type == WHITE_SPACE || is_quote(tmp->type)))
					tmp = tmp->next;
				if (tmp && tmp->type == ENV)
					tmp->type = WORD;
			}
		}
		head = head->next;
	}
}

void expand_env(t_data *data)
{
	t_elem	*head;

	check_here_doc_variable(data);
	head = data->tokens;
	while (head)
	{
		if (head->type == ENV)
			get_env_value(head);
		head = head->next;
	}
}
