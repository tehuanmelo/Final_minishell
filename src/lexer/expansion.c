/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:10:33 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/24 17:49:14 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_var(char *content)
{
	char	**env;
	char	*str;
	int		len;
	int		i;

	env = g_data.env;
	str = NULL;
	len = ft_strlen(content);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(content, env[i], len) == 0 && env[i][len] == '=')
			str = ft_strdup(&env[i][len + 1]);
		env++;
	}
	return (str);
}

void	get_env_value(t_elem *tokens)
{
	char	*str;
	char	*content;

	content = tokens->content;
	if ((!ft_isalpha(content[1]) && content[1] != '_'))
		tokens->type = WORD;
	else
	{
		str = get_env_var(&content[1]);
		if (str)
		{
			tokens->content = str;
			tokens->len = ft_strlen(str);
		}
		else
		{
			if (!ft_strcmp(tokens->content, "$EMPTY"))
				g_data.exit_code = 0;
			tokens->content = "";
			tokens->len = 0;
			tokens->type = EMPTY;
		}
	}
	free(content);
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

void	check_exit_variable(t_data *data)
{
	t_elem	*head;
	char	*tmp;
	char	*env_exit;

	head = data->tokens;
	while (head)
	{
		if (head->type == ENV)
		{
			if (!ft_strcmp(head->content, "$?"))
			{
				tmp = head->content;
				env_exit = ft_itoa(data->exit_code);
				head->content = env_exit;
				head->type = EXIT_STATUS;
				head->len = ft_strlen(env_exit);
				free(tmp);
			}
		}
		head = head->next;
	}
}

void	expand_env(t_data *data)
{
	t_elem	*head;

	check_here_doc_variable(data);
	check_exit_variable(data);
	head = data->tokens;
	while (head)
	{
		if (head->type == ENV)
			get_env_value(head);
		head = head->next;
	}
}
