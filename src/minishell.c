/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:47 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/23 15:14:53 by mbin-nas         ###   ########.fr       */
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
		exit_shell3(&data, data.exit_code);
	}
	if (strcmp(*input, "") == 0)
	{
		free(*input);
		return (1);
	}
	if (strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void	init_shell(t_data *data)
{
	if (!sintax_error(data))
	{
		data->cmd_lst = parser(data);
		data->exit_code = execute(data);
		// if(access())
		int i = 0;
		while (i <= data->command_index)
		{
			char *str1 = ft_itoa(i); 
			char *str = ft_strjoin("/tmp/.here_doc", str1);
			if (access(str, F_OK) == 0)
				unlink(str);
			i++;
			free(str1);
			free(str);
		}
		
		// printf("%d\n", data->command_index);
		free_data(data, data->cmd_lst, false);
		free_commands(data->cmd_lst);
	}
	else
	{
		free(data->input);
		return ;
	}
}
