/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:30:39 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/24 21:29:09 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// bool	restore_io(t_io_fds *io)
// {
// 	int	ret;

// 	ret = true;
// 	if (!io)
// 		return (ret);
// 	if (io->stdin_backup != -1)
// 	{
// 		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
// 			ret = false;
// 		close(io->stdin_backup);
// 		io->stdin_backup = -1;
// 	}
// 	if (io->stdout_backup != -1)
// 	{
// 		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
// 			ret = false;
// 		close(io->stdout_backup);
// 		io->stdout_backup = -1;
// 	}
// 	return (ret);
// }

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

void	heredoc_stupid_fds(int fd_out, int command_index)
{
	char	*str1;
	char	*str;
	(void)fd_out;

	str1 = ft_itoa(command_index);
	str = ft_strjoin("/tmp/.here_doc", str1);
	if (g_data.heredoc_fd != -1)
		close(g_data.heredoc_fd);
	g_data.heredoc_fd = open(str, O_RDONLY);
	if (g_data.heredoc_fd != -1)
		dup2(g_data.heredoc_fd, STDIN_FILENO);
	free(str1);
	free(str);
	// if (fd_out != -1)
	// {
	// 	close(fd_out);
	// 	fd_out = -1;
	// }
}

bool	redirect_io(t_io_fds *io, int command_index)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	// io->stdin_backup = dup(STDIN_FILENO);
	// if (io->stdin_backup == -1)
	// 	ret = error_msg_commad("dup", "stdin backup", strerror(errno), false);
	// io->stdout_backup = dup(STDOUT_FILENO);
	// if (io->stdout_backup == -1)
	// 	ret = error_msg_commad("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
	{
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = error_msg_commad("dup2", io->infile, strerror(errno), false);
		printf("closing fd in %d\n", io->fd_in);
		close(io->fd_in);
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = error_msg_commad("dup2", io->outfile, strerror(errno), false);
		printf("closing fd out %d\n", io->fd_out);
		close(io->fd_out);
	}
	heredoc_stupid_fds(io->fd_out, command_index);
	return (ret);
}
