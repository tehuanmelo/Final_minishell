/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:09:53 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/19 21:01:46 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_built_ins(t_data *data, t_cmd *check_cmd)
{
	int	result;

	result = COMMAND_NOT_FOUND;
	if (ft_strncmp(check_cmd->command, "cd", 3) == 0)
		result = ft_cd_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "echo", 5) == 0)
		result = ft_echo_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "env", 4) == 0)
		result = ft_env_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "export", 7) == 0)
		result = ft_export_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "pwd", 4) == 0)
		result = ft_pwd_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "unset", 6) == 0)
		result = ft_unset_built_in(data, check_cmd->args);
	else if (ft_strncmp(check_cmd->command, "exit", 5) == 0)
		result = ft_exit_built_in(data, check_cmd->args);
	return (result);
}

static int	execute_system_binaries(t_data *data, t_cmd *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (COMMAND_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (COMMAND_NOT_FOUND);
	cmd->path = fetch_command_path(data, cmd->command);
	if (!cmd->path)
		return (COMMAND_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		error_msg_commad("execve: ", NULL, strerror(errno), errno);
	}
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_data *data, t_cmd *cmd)
{
	int	result;

	result = check_command_not_found(data, cmd);
	if (result != 0)
		{
			printf("Exit 2\n");
			exit_shell(data, result);
		}
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		error_msg_commad("execve: ", NULL, strerror(errno), errno);
	}
	return (EXIT_FAILURE);
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
	while (args[i])
	{
		free(args[i++]);
	}
	free(args);
	return (new_args);
}

// int execute_commands(t_data *data, t_cmd *cmd)
// {
//     // printf("The command reached execute commands %s\n", cmd->command);
//     int ret;
//     if (data->exit_code != EXIT_SUCCESS)
//         exit(data->exit_code);
//     if (!check_here_doc(cmd->args))
//     {
//         here_doc(cmd->args);
//         cmd->args = remove_heredoc_args(cmd->args);
//         cmd->io_fds->fd_in = open("/tmp/.here_do.c", O_RDONLY);
//         if (cmd->io_fds->fd_in < 0)
//         {
//             perror("open");
//             exit(EXIT_FAILURE);
//         }
//     }
//     set_pipe_fds(data->cmd_lst, cmd);
//     redirect_io(cmd->io_fds);
//     close_fds(cmd, false);
//     ret = execute_built_ins(data, cmd);
//     if (ret != COMMAND_NOT_FOUND)
//     {
//         exit(ret);
//     }
//     if (ft_strchr(cmd->command, '/') == NULL)
//         ret = execute_system_binaries(data, cmd);
//     else
//         cmd->path = cmd->command;
//     ret = execute_local_bin(data, cmd);
//     exit_shell(data, ret);
//     return (ret);
// }

int	execute_commands(t_data *data, t_cmd *cmd, int command_index)
{
	printf("Which one is this\n");
	int	ret;
	
	if (data->exit_code != EXIT_SUCCESS)
		exit_shell(data, data->exit_code);
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd_lst, cmd);
	redirect_io(cmd->io_fds, command_index);
	close_fds(cmd, false);
	ret = execute_built_ins(data, cmd);
	if (ret != COMMAND_NOT_FOUND)
		{
			printf("About to call \n");
			exit_shell(data, ret);
		}
	if (ft_strchr(cmd->command, '/') == NULL)
		ret = execute_system_binaries(data, cmd);
	else
		cmd->path = cmd->command;
	ret = execute_local_bin(data, cmd);
	printf("About to call 2\n");
	exit_shell(data, ret);
	return (ret);
}
