/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:10:01 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/20 18:31:16 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	if (data->exit_code != EXIT_SUCCESS)
		return (data->exit_code);
	close_fds(data->cmd_lst, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/* create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/
static int	create_children(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	cmd = data->cmd_lst;
	i = 0;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (error_msg_commad("fork", NULL, strerror(errno),
					EXIT_FAILURE));
		else if (data->pid == 0)
		{
			execute_commands(data, cmd, i);
		}
		i++;
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* execution_prep:
*	Prepares the command list for execution, creates pipes
*	and checks the input and output files.
*	Returns false in case of error, true if all is ready to
*	execute.
*/
static int	execution_prep(t_data *data)
{
	if (!data || !data->cmd_lst)
		return (EXIT_SUCCESS);
	if (!data->cmd_lst->command)
	{
		if (data->cmd_lst->io_fds
			&& !check_infile_outfile(data->cmd_lst->io_fds))
		{
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (COMMAND_NOT_FOUND);
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.
*/
int	execute(t_data *data)
{
	int		ret;
	t_cmd	*current_cmd;
	int		should_print;
	int		i;

	printf("WHo am I \n");
	current_cmd = data->cmd_lst;
	ret = execution_prep(data);
	if (ret != COMMAND_NOT_FOUND)
	{
		printf("Whaaat\n");
		return (ret);
	}
	if (!data->cmd_lst->next && !data->cmd_lst->prev
		&& check_infile_outfile(data->cmd_lst->io_fds))
	{
		if (!check_here_doc(current_cmd->args))
		{
			should_print = 1;
			if (current_cmd->next)
			{
				if (!check_here_doc(current_cmd->next->args))
				{
					should_print = 0;
				}
			}
			here_doc(current_cmd->args, should_print, 0);
			current_cmd->args = remove_heredoc_args(current_cmd->args);
		}
		redirect_io(data->cmd_lst->io_fds, 0);
		ret = execute_built_ins(data, data->cmd_lst);
		restore_io(data->cmd_lst->io_fds);
		if (ret != COMMAND_NOT_FOUND)
			return (ret);
	}
	i = 0;
	while (current_cmd)
	{
		if (!check_here_doc(current_cmd->args))
		{
			here_doc(current_cmd->args, 1, i);
			current_cmd->args = remove_heredoc_args(current_cmd->args);
		}
		i++;
		current_cmd = current_cmd->next;
	}
	ret = create_children(data);
	restore_io(data->cmd_lst->io_fds);
	close_fds(data->cmd_lst, true);
	return (ret);
}
