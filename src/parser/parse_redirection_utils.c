/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:51:20 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 19:02:04 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirection_operator(const char *s)
{
	return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0 || ft_strcmp(s,
			"<") == 0);
}

int	infile_call(t_cmd *cmd, int index)
{
	char	*missing_filename;

	missing_filename = ft_strdup(cmd->args[index + 1]);
	g_data.exit_code = error_msg_commad(missing_filename, NULL,
			strerror(errno), 1);
	return (free(missing_filename), g_data.exit_code);
}

int	handle_outfile_utils(t_cmd *cmd, int index)
{
	if (cmd->io_fds->fd_out == -1)
	{
		g_data.exit_code = error_msg_commad(cmd->args[index + 1], NULL,
				strerror(errno), 1);
		return (g_data.exit_code);
	}
	if (cmd->args[index + 2] != NULL
		&& !is_redirection_operator(cmd->args[index + 2]))
	{
		write(cmd->io_fds->fd_out, cmd->args[index + 2],
			ft_strlen(cmd->args[index + 2]));
		free(cmd->args[index + 2]);
		cmd->args[index + 2] = NULL;
	}
	return (g_data.exit_code);
}
