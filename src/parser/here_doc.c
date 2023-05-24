/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:16:07 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/24 17:17:28 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	heredoc_readline(char **input)
{
	*input = readline(HD_PROMPT);
	if (!*input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	write_heredoc_file(char **delimiter, int nbr_heredocs, t_data *data)
{
	int		line_writen;
	int		nl_writen;
	char	*line;
	int		status;
	int		i;

	i = 0;
	while (1)
	{
		status = heredoc_readline(&line);
		if (nbr_heredocs > 1)
			checking_delimiter_index(&nbr_heredocs, &i, delimiter, line);
		else
		{
			if (status == EXIT_FAILURE || (ft_strcmp(line, delimiter[i]) == 0))
				break ;
			line_writen = write(data->heredoc_fd, line, ft_strlen(line));
			nl_writen = write(data->heredoc_fd, "\n", 1);
			if (line_writen == -1 || nl_writen == -1)
				break ;
		}
		free(line);
	}
	if (line)
		free(line);
}

int	execute_heredoc(char **delimiter, int command_index, int nbr_heredocs)
{
	t_data	*new_data;
	char	*str1;
	char	*str;

	str1 = ft_itoa(command_index);
	str = ft_strjoin("/tmp/.here_doc", str1);
	new_data = &data;
	new_data->heredoc_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (new_data->heredoc_fd == -1)
	{
		free(str1);
		free(str);
		return (EXIT_FAILURE);
	}
	write_heredoc_file(delimiter, nbr_heredocs, new_data);
	close(new_data->heredoc_fd);
	free_delimiter(delimiter);
	free(str1);
	free(str);
	new_data->heredoc_fd = -1;
	return (EXIT_SUCCESS);
}

void	here_doc(char **args, int should_print, int command_index)
{
	char	**delimiter;
	int		status;
	pid_t	pid;
	int		nbr_heredocs;

	data.command_index = command_index;
	nbr_heredocs = get_heredoc_nbr(args);
	pid = fork();
	if (pid == 0)
	{
		delimiter = get_delimiter(args, nbr_heredocs);
		if (should_print)
			execute_heredoc(delimiter, command_index, nbr_heredocs);
		exit_shell(&data, EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		init_signals();
	}
}
