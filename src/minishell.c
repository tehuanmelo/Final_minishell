/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:47 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/25 19:13:52 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_data(t_data *data, char *str)
{
	data->nb_cmd = 0;
	data->input = str;
	data->tokens = get_tokens_list(data->input);
	data->heredoc_fd = -1;
}

int	_readline_(char **input)
{
	char	*tmp;

	tmp = readline(MINI_PROMPT);
	*input = ft_strtrim(tmp, " ");
	free(tmp);
	if (!*input)
	{
		ft_putstr("exit\n");
		exit_shell3(&g_data, g_data.exit_code);
	}
	if (ft_strcmp(*input, "") == 0)
	{
		free(*input);
		return (1);
	}
	if (strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void	close_fd(void)
{
	t_cmd	*temp;

	temp = g_data.cmd_lst;
	while (temp->next)
		temp = temp->next;
	if (temp->io_fds->fd_out != -1)
		close(temp->io_fds->fd_out);
	if (temp->io_fds->fd_in != -1)
		close(temp->io_fds->fd_in);
}

void	init_shell(t_data *data)
{
	int		i;
	char	*str1;
	char	*str;

	if (!sintax_error(data))
	{
		data->cmd_lst = parser(data);
		data->exit_code = execute(data);
		i = 0;
		while (i <= data->command_index)
		{
			str1 = ft_itoa(i);
			str = ft_strjoin("/tmp/.here_doc", str1);
			if (access(str, F_OK) == 0)
				unlink(str);
			i++;
			free(str1);
			free(str);
		}
		close_fd();
		free_data(data, data->cmd_lst, false);
		free_commands(data->cmd_lst);
	}
	else
		return (free(data->input));
}
