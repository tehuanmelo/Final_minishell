/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:16:07 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/23 15:13:58 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_here_doc(char **args)
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

char **get_delimiter(char **input, int nbr_heredocs)
{
	char **delimiter;
	int i;

	delimiter = ft_calloc(nbr_heredocs + 1, sizeof(char *));
	i = 0;
	while (*input)
	{
		if (!ft_strcmp("<<", *input))
		{
			delimiter[i++] = ft_strdup(*(++input));
		}
		input++;
	}
	return (delimiter);
}

int heredoc_readline(char **input)
{
	*input = readline(HD_PROMPT);
	if (!*input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void checking_delimiter_index(int *nbr_heredocs, int *i, char **delimiter, char *line)
{
	if (ft_strcmp(line, delimiter[*i]) == 0)
	{
		(*nbr_heredocs)--;
		(*i)++;
	}
}

void write_heredoc_file(char **delimiter, int nbr_heredocs, t_data *data)
{
	int line_writen;
	int nl_writen;
	char *line;
	int status;
	int i;

	i = 0;
	while (1)
	{
		status = heredoc_readline(&line);
		if (nbr_heredocs > 1)
			checking_delimiter_index(&nbr_heredocs, &i, delimiter, line);
		else
		{
			if (status == EXIT_FAILURE || (ft_strcmp(line, delimiter[i]) == 0))
				break;
			line_writen = write(data->heredoc_fd, line, ft_strlen(line));
			nl_writen = write(data->heredoc_fd, "\n", 1);
			if (line_writen == -1 || nl_writen == -1)
				break;
		}
		free(line);
	}
	if (line)
		free(line);
}

void free_delimiter(char **delimiter)
{
	int i;

	i = 0;
	while (delimiter[i])
		free(delimiter[i++]);
	free(delimiter);
}

int execute_heredoc(char **delimiter, int command_index, int nbr_heredocs)
{
	t_data *new_data;
	char *str1;
	char *str;

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

int get_heredoc_nbr(char **args)
{
	int i;
	int nbr_heredocs;

	i = 0;
	nbr_heredocs = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			nbr_heredocs++;
		i++;
	}
	return (nbr_heredocs);
}

void here_doc(char **args, int should_print, int command_index)
{
	char **delimiter;
	int status;
	pid_t pid;
	int nbr_heredocs;

	data.command_index = command_index;
	nbr_heredocs = get_heredoc_nbr(args);
	pid = fork();
	if (pid == 0)
	{
		delimiter = get_delimiter(args, nbr_heredocs);
		if (should_print)
			execute_heredoc(delimiter, command_index, nbr_heredocs); //     print_file_contents("/tmp/.here_do.c");
		exit_shell(&data, EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		init_signals();
	}
}
