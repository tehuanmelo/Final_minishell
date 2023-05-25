/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:30:39 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 18:28:37 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

void	heredoc_stupid_fds(int command_index)
{
	char	*str1;
	char	*str;

	str1 = ft_itoa(command_index);
	str = ft_strjoin("/tmp/.here_doc", str1);
	if (g_data.heredoc_fd != -1)
		close(g_data.heredoc_fd);
	g_data.heredoc_fd = open(str, O_RDONLY);
	if (g_data.heredoc_fd != -1)
		dup2(g_data.heredoc_fd, STDIN_FILENO);
	free(str1);
	free(str);
}

bool	redirect_io(t_io_fds *io, int command_index)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->fd_in != -1)
	{
		dup2(io->fd_in, STDIN_FILENO);
		close(io->fd_in);
	}
	if (io->fd_out != -1)
	{
		dup2(io->fd_out, STDOUT_FILENO);
		close(io->fd_out);
	}
	heredoc_stupid_fds(command_index);
	return (ret);
}
