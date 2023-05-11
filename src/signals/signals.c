/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:08:12 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/11 14:57:56 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



void sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigint_handler_heredoc(int sig)
{
    (void)sig;
	t_data *data_ = &data;
	if (data_->heredoc_fd != -1) 
	{
        close(data_->heredoc_fd);
		unlink("/tmp/.here_doc");
		ft_putstr_fd("\n", STDOUT_FILENO);
    }
	exit_shell(&data, EXIT_FAILURE);
}

void init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}