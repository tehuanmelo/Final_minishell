/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:32:30 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 19:01:37 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	g_data;

int	handle_outfile_redirection(t_cmd *cmd, int index)
{
	int	open_flag;

	open_flag = O_WRONLY | O_CREAT;
	if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
		return (COMMAND_NOT_FOUND);
	if (ft_strcmp(cmd->args[index], ">") == 0)
		open_flag |= O_TRUNC;
	else if (ft_strcmp(cmd->args[index], ">>") == 0)
		open_flag |= O_APPEND;
	if (cmd->io_fds->fd_out != -1)
		close(cmd->io_fds->fd_out);
	cmd->io_fds->fd_out = open(cmd->args[index + 1], open_flag, 0644);
	g_data.exit_code = handle_outfile_utils(cmd, index);
	free(cmd->args[index]);
	cmd->args[index] = NULL;
	free(cmd->args[index + 1]);
	cmd->args[index + 1] = NULL;
	return (EXIT_SUCCESS);
}

int	handle_infile_redirection(t_cmd *cmd, int index)
{
	int		last_fd_in;

	last_fd_in = -1;
	if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
		return (COMMAND_NOT_FOUND);
	if (last_fd_in != -1)
		close(last_fd_in);
	if (cmd->args[index + 2] && !is_redirection_operator(cmd->args[index + 2]))
		last_fd_in = open(cmd->args[index + 2], O_RDONLY);
	else
		last_fd_in = open(cmd->args[index + 1], O_RDONLY);
	if (last_fd_in == -1)
		return (infile_call(cmd, index));
	cmd->io_fds->fd_in = last_fd_in;
	if (last_fd_in != -1)
	{
		close(last_fd_in);
		last_fd_in = -1;
	}
	free(cmd->args[index]);
	cmd->args[index] = NULL;
	free(cmd->args[index + 1]);
	cmd->args[index + 1] = NULL;
	return (EXIT_SUCCESS);
}

int	call_heredoc_outfile(t_cmd *cmd, int *i, int *error_occurred)
{
	if (handle_outfile_redirection(cmd, *i) != EXIT_SUCCESS)
	{
		*error_occurred = 1;
		return (1);
	}
	*i += 2;
	return (0);
}

int	call_heredoc_infile(t_cmd *cmd, int *i, int *error_occurred)
{
	if (handle_infile_redirection(cmd, *i) != EXIT_SUCCESS)
	{
		*error_occurred = 1;
		return (EXIT_FAILURE);
	}
	if (cmd->args[*i + 2] && !is_redirection_operator(cmd->args[*i + 2]))
		*i += 3;
	else
		*i += 2;
	return (0);
}

int	parse_redirection(t_cmd *cmd)
{
	int	i;
	int	error_occurred;

	i = 0;
	error_occurred = 0;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i],
				">>") == 0)
		{
			if (call_heredoc_outfile(cmd, &i, &error_occurred) == 1)
				break ;
		}
		else if (ft_strcmp(cmd->args[i], "<") == 0)
		{
			if (call_heredoc_infile(cmd, &i, &error_occurred) == 1)
				break ;
		}
		else
			i++;
	}
	return (error_occurred);
}
