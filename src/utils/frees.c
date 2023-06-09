/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:18:14 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 18:43:02 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*free_io(t_io_fds *io)
{
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
	return (NULL);
}

void	free_commands2(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	char	**tmp_str;
	int		i;

	while (cmds)
	{
		if (cmds->io_fds)
			cmds->io_fds = free_io(cmds->io_fds);
		tmp_cmd = cmds;
		tmp_str = cmds->args;
		i = 0;
		while (cmds->args[i])
			free(cmds->args[i++]);
		free(cmds->args[i]);
		free(tmp_str);
		cmds = cmds->next;
		free(tmp_cmd);
	}
}

void	free_commands(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	char	**tmp_str;
	int		i;

	while (cmds)
	{
		if (cmds->io_fds)
			cmds->io_fds = free_io(cmds->io_fds);
		tmp_cmd = cmds;
		tmp_str = cmds->args;
		i = 0;
		while (cmds->args[i])
			free(cmds->args[i++]);
		free(tmp_str);
		if (cmds->command && cmds->command != NULL)
			free(cmds->command);
		cmds = cmds->next;
		free(tmp_cmd);
	}
}

void	free_heredoc_args(char **args, int i)
{
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_data(t_data *data, t_cmd *cmds, bool flag)
{
	if (data && data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (cmds->io_fds->fd_out != -1)
	{
		close(cmds->io_fds->fd_out);
		cmds->io_fds->fd_out = -1;
	}
	if (data && data->tokens)
		lstclear_token(&data->tokens, &free_ptr);
	cmds->io_fds = free_io(cmds->io_fds);
	if (flag == true)
	{
		if (data && data->current_dir)
			free_ptr(data->current_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env)
			free_str_tab(data->env);
		rl_clear_history();
	}
}
