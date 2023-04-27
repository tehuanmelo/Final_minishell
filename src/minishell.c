/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:47 by tde-melo          #+#    #+#             */
/*   Updated: 2023/04/27 14:32:52 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void run_cmd(t_data *data)
{
	int pid;
	char **args;
	int status;

	args = data->cmd_lst->args;
	if (!check_here_doc(args))
		here_doc(args);
	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(*args, "echo") == 0)
			execv("/bin/echo", args);
		else if (ft_strcmp(*args, "pwd") == 0)
			execv("/bin/pwd", args);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		init_signals();
	}
}

void set_data(t_data *data, char *str)
{
	data->nb_cmd = 0;
	data->input = ft_strtrim(str, " ");
	data->tokens = get_tokens_list(data->input);
	data->heredoc_fd = -1;
}

int _readline_(char **input)
{
	fprintf(stderr, " Hello I am working \n");
	*input = readline(MINI_PROMPT);
	if (!*input)
	{
		fprintf(stderr, "Input: %s\n", *input);
		ft_putstr("exittttt\n");
		exit(1);
	}
	if (strcmp(*input, "") == 0)
		return (1);
	if (strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void init_shell(t_data *data)
{
	if (!sintax_error(data))
		data->cmd_lst = parser(data);
		// here_doc(data.cmd_lst->args);
		// run_cmd(data);
}

