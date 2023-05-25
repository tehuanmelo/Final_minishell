/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:33:34 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 19:25:03 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->heredoc_fd != -1)
			close(data->heredoc_fd);
		if (data->cmd_lst)
			close_fds(data->cmd_lst, true);
		free_data(data, data->cmd_lst, true);
		free_commands(data->cmd_lst);
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
