/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:33:34 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/19 20:11:22 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.
*/
void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd_lst)
			close_fds(data->cmd_lst, true);
		free_data(data, data->cmd_lst, true);
		free_commands(data->cmd_lst);
		free_tokens_list(data->tokens);
	}
	exit(exno);
}

void	exit_shell2(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd_lst && data->cmd_lst->io_fds)
			close_fds(data->cmd_lst, true);
		free_data(data, data->cmd_lst, true);
		free_commands2(data->cmd_lst);
		free_tokens_list(data->tokens);
	}
	exit(exno);
}

void	exit_shell3(t_data *data, int exno)
{
	if (data)
	{
		// if (data->cmd_lst && data->cmd_lst->io_fds)
		// 	close_fds(data->cmd_lst, true);
		if (data && data->input)
		{
			free(data->input);
			data->input = NULL;
		}
		if (data && data->tokens)
			lstclear_token(&data->tokens, &free_ptr);
		if (data && data->current_dir)
			free_ptr(data->current_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env)
			free_str_tab(data->env);
		rl_clear_history();
	}
	exit(exno);
}
