/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executives_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:09:57 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 16:58:24 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	cmd_is_dir(char *cmd)
{
	struct stat	command_status;

	ft_memset(&command_status, 0, sizeof(command_status));
	stat(cmd, &command_status);
	return (S_ISDIR(command_status.st_mode));
}

char	**remove_heredoc_args(char **args)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	while (args[i] != NULL)
		i++;
	new_args = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "<<") != 0 && (i == 0 || ft_strcmp(args[i - 1],
					"<<") != 0))
		{
			new_args[j] = ft_strdup(args[i]);
			j++;
		}
		i++;
	}
	new_args[j] = NULL;
	i = 0;
	free_heredoc_args(args, i);
	return (new_args);
}

int	check_command_not_found(t_data *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& fetch_env_variable_index(data->env, "PATH") != -1)
		return (error_msg_commad(cmd->command, NULL, "command not found",
				COMMAND_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (error_msg_commad(cmd->command, NULL, strerror(errno),
				COMMAND_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (error_msg_commad(cmd->command, NULL, "is a directory",
				COMMAND_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (error_msg_commad(cmd->command, NULL, strerror(errno),
				COMMAND_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
