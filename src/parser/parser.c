/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:07:15 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/05 14:09:25 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


char	*get_string(t_elem **head)
{
	char	*str;

	str = "";
	while ((*head) && (*head)->type != WHITE_SPACE)
	{
		if (!is_quote((*head)->type) && (*head)->type != PIPE)
			str = ft_strjoin(str, (*head)->content);
		*head = (*head)->next;
	}
	return (str);
}

char	**get_args(t_elem **counter, t_elem **head)
{
	int		nbr_args;
	int		i;
	char	**args;

	nbr_args = count_args(&(*counter));
	args = ft_calloc(nbr_args + 1, sizeof(char *));
	if ((*head) && (*head)->type == PIPE)
		(*head) = (*head)->next;
	i = 0;
	while ((*head) && (*head)->type != PIPE)
	{
		if ((*head)->type != WHITE_SPACE && !is_quote((*head)->type)
			&& (*head)->type != EMPTY)
			args[i++] = get_string(&(*head));
		if ((*head))
			(*head) = (*head)->next;
	}
	return (args);
}

t_cmd	*parser(t_data *data)
{
	t_cmd	*new;
	t_cmd	*head;
	t_elem	*head_counter;
	t_elem	*tmp;
	int		nbr_commands;

	new = NULL;
	head = NULL;
	head_counter = data->tokens;
	tmp = data->tokens;
	nbr_commands = count_commands(data);
	// printf("Inside parser: number of commands = %d\n", nbr_commands); 
	while (nbr_commands--)
	{
		new = new_command();
		new->args = get_args(&head_counter, &tmp);
		new->command = new->args[0];
        // init_io(new);
		// parse_redirection(new);
		append_command(&head, new);
		// printf("Inside parser: command = %s\n", new->command); 
	}
	return (head);
}
