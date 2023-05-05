/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:07:15 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/05 14:05:36 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*new_command(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
    new->command = NULL;
    new->path = NULL;
    new->pipe_fd[0] = -1;
    new->pipe_fd[1] = -1;
    new->io_fds = NULL;
    new->prev = NULL;
    new->next = NULL;
	return (new);
}

void	append_command(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

int	count_commands(t_data *data)
{
	t_elem	*tmp;
	int		count;

	tmp = data->tokens;
	count = 0;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->state == GENERAL)
			count++;
		tmp = tmp->next;
	}
	return (count + 1);
}

int	count_args(t_elem **head)
{
	int	i;

	i = 0;
	if ((*head)->type == PIPE)
		(*head) = (*head)->next;
	while ((*head) && (*head)->type != PIPE)
	{
		if ((*head)->type != WHITE_SPACE && !is_quote((*head)->type))
			i++;
		*head = (*head)->next;
	}
	return (i);
}

void free_commands(t_cmd *cmds)
{
	t_cmd *tmp_cmd;
	char **tmp_str;
	
	while (cmds)
	{
		tmp_cmd = cmds;
		tmp_str = cmds->args;
		while (*(cmds->args))
			free(*(cmds->args)++);
		free(tmp_str);
		cmds = cmds->next;
		free(tmp_cmd);
	}
}
