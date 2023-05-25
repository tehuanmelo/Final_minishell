/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:30:44 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 18:52:55 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd)
		{
			if (cmds->pipe_fd[0] != -1 && cmds->pipe_fd[0] != STDIN_FILENO)
				close(cmds->pipe_fd[0]);
			if (cmds->pipe_fd[1] != -1 && cmds->pipe_fd[1] != STDOUT_FILENO)
				close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

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

bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev)
	{	
		if (c->io_fds->fd_in == -1)
			dup2(c->prev->pipe_fd[0], STDIN_FILENO);
		if (c->prev->pipe_fd[0] != -1)
			close(c->prev->pipe_fd[0]);
	}
	if (c->next)
	{
		if (c->io_fds->fd_out == -1)
			dup2(c->pipe_fd[1], STDOUT_FILENO);
		if (c->pipe_fd[1] != -1)
			close(c->pipe_fd[1]);
	}
	close_pipe_fds(cmds, c);
	return (true);
}
