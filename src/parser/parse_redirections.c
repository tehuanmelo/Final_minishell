/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:32:30 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/24 17:19:59 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	data;

int	is_redirection_operator(const char *s)
{
	return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0 || ft_strcmp(s,
			"<") == 0);
}

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
	if (cmd->io_fds->fd_out == -1)
	{
		data.exit_code = error_msg_commad(cmd->args[index + 1], NULL,
				strerror(errno), 1);
		return (data.exit_code);
	}
	if (cmd->args[index + 2] != NULL
		&& !is_redirection_operator(cmd->args[index + 2]))
	{
		write(cmd->io_fds->fd_out, cmd->args[index + 2],
			ft_strlen(cmd->args[index + 2]));
		free(cmd->args[index + 2]);
		cmd->args[index + 2] = NULL;
	}
	free(cmd->args[index]);
	cmd->args[index] = NULL;
	free(cmd->args[index + 1]);
	cmd->args[index + 1] = NULL;
	return (EXIT_SUCCESS);
}

int	handle_infile_redirection(t_cmd *cmd, int index)
{
	static int	last_fd_in;
	char		*missing_filename;

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
	{
		missing_filename = ft_strdup(cmd->args[index + 1]);
		data.exit_code = error_msg_commad(missing_filename, NULL,
				strerror(errno), 1);
		free(missing_filename);
		return (data.exit_code);
	}
	cmd->io_fds->fd_in = last_fd_in;
	free(cmd->args[index]);
	cmd->args[index] = NULL;
	free(cmd->args[index + 1]);
	cmd->args[index + 1] = NULL;
	return (EXIT_SUCCESS);
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
			if (handle_outfile_redirection(cmd, i) != EXIT_SUCCESS)
			{
				error_occurred = 1;
				break ;
			}
			i += 2;
		}
		else if (ft_strcmp(cmd->args[i], "<") == 0)
		{
			if (handle_infile_redirection(cmd, i) != EXIT_SUCCESS)
			{
				error_occurred = 1;
				break ;
			}
			if (cmd->args[i + 2] && !is_redirection_operator(cmd->args[i + 2]))
				i += 3;
			else
				i += 2;
		}
		else
			i++;
	}
	return (error_occurred);
}
