/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:16:07 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/23 14:42:13 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_here_doc(char **args)
{
	while (*args)
	{
		if (!ft_strcmp(*args, "<<"))
			return (0);
		args++;
	}
	data.heredoc_call = true;
	return (1);
}

char	*get_delimiter(char **input, int delimier_index)
{
	char	*delimiter;
	(void)delimier_index;
	
	delimiter = NULL;
	while (*input)
	{ 
		if (!ft_strcmp("<<", *input))
		{
			delimiter = *(++input);
		}
		input++;
	}
	return (delimiter);
}

int	heredoc_readline(char **input)
{
	*input = readline(HD_PROMPT);
	if (!*input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute_heredoc(char *delimiter, int command_index)
{
	
	int		line_writen;
	int		nl_writen;
	char	*line;
	int		status;
	t_data	*data_;
	char *str1 = ft_itoa(command_index); 
	char *str = ft_strjoin("/tmp/.here_do.c", str1);
	
	data_ = &data;
	data_->heredoc_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	if (data_->heredoc_fd == -1)
		{
			free(str1);
			free(str);
			return (EXIT_FAILURE);
		}
	while (1)
	{
		status = heredoc_readline(&line);
		if (status == EXIT_FAILURE || (ft_strcmp(line, delimiter) == 0))
			break ;
		line_writen = write(data_->heredoc_fd, line, ft_strlen(line));
		nl_writen = write(data_->heredoc_fd, "\n", 1);
		if (line_writen == -1 || nl_writen == -1)
			break ;
		free(line);
	}
	free(str1);
	free(str);
	close(data_->heredoc_fd);
	data_->heredoc_fd = -1;
	return (EXIT_SUCCESS);
}

void here_doc(char **args, int should_print, int command_index)
{
	char	*delimiter;
	int		status;
	pid_t	pid;
	int		delimiter_index = 0;
	
data.command_index = command_index;
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, sigint_handler_heredoc);
        delimiter = get_delimiter(args, delimiter_index);
		printf("I am getting the delimiter %s\n", delimiter);
        if (should_print)
			execute_heredoc(delimiter , command_index);   //     print_file_contents("/tmp/.here_do.c");
        exit_shell(&data, EXIT_SUCCESS);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        init_signals();
    }
}
