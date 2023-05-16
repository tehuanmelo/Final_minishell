/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:30:44 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/16 14:31:39 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.
*/
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd[0] != -1 && cmds->pipe_fd[1]
			!= -1)
		{
			if (cmds->pipe_fd[0] != STDIN_FILENO)
				close(cmds->pipe_fd[0]);
			if (cmds->pipe_fd[1] != STDOUT_FILENO)
				close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

/* create_pipes:
*	Creates a set of pipes for each piped command in the list
*	of commands.
*	Returns 1 if successful, 0 in case of failure.
*/
bool	create_pipes(t_data *data)
{
	int		fd[2];
	t_cmd	*tmp;

	tmp = data->cmd_lst;
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(fd) != 0)
			{
				return (false);
			}
			tmp->pipe_fd[0] = fd[0];
			tmp->pipe_fd[1] = fd[1];
		}
		tmp = tmp->next;
	}
	return (true);
}

/* set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output ad the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns true when the pipe file descriptors are set.
*/
bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev)
	{
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
		close(c->prev->pipe_fd[1]);
	}
	if (c->next)
	{
		dup2(c->pipe_fd[1], STDOUT_FILENO);
		close(c->pipe_fd[0]);
	}
	close_pipe_fds(cmds, c);
	return (true);
}
