/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:07:15 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/07 15:33:59 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_string(t_elem **head)
{
	char *str;

	str = NULL;
	if ((is_redir((*head)->type)))
		str = join_string(str, (*head)->content);
	else
	{
		while ((*head))
		{
			if (*head && ((*head)->type == WHITE_SPACE || (*head)->type == PIPE || is_redir((*head)->type)))
				break;
			if (*head && ((*head)->type == WORD || (*head)->type == ENV || (*head)->type == EXIT_STATUS))
				str = join_string(str, (*head)->content);
			*head = (*head)->next;
		}
		if (*head)
			*head = (*head)->prev;
	}
	return (str);
}

char **get_args(t_elem **counter, t_elem **head)
{
	int nbr_args;
	int i;
	char **args;

	nbr_args = count_args(&(*counter));
	args = ft_calloc(nbr_args + 1, sizeof(char *));
	if ((*head) && (*head)->type == PIPE)
		(*head) = (*head)->next;
	i = 0;
	while ((*head) && (*head)->type != PIPE)
	{
		if ((*head)->type != WHITE_SPACE && !is_quote((*head)->type) && (*head)->type != EMPTY)
			args[i++] = get_string(&(*head));
		if (*head)
			(*head) = (*head)->next;
	}
	return (args);
}

t_cmd *parser(t_data *data)
{
    t_cmd *new;
    t_cmd *head;
    t_elem *head_counter;
    t_elem *tmp;
    int nbr_commands;
    // int error_occurred = 0;

    new = NULL;
    head = NULL;
    head_counter = data->tokens;
    tmp = data->tokens;
    nbr_commands = count_commands(data);

    while (nbr_commands--)
    {
        new = new_command();
        new->args = get_args(&head_counter, &tmp);
        new->command = new->args[0];
        init_io(new);
        data->exit_code = parse_redirection(new);
        append_command(&head, new);
    }
    return head;
}

