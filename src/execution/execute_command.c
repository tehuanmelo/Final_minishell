#include "../../inc/minishell.h"


int execute_built_ins(t_data *data, t_cmd *check_cmd)
{
    int result;

    result = COMMAND_NOT_FOUND;
    // printf("Inside execute_built_ins: cmd->command = %s\n", check_cmd->command);
    if(ft_strncmp(check_cmd->command, "cd", 3) == 0)
        result = ft_cd_built_in(data, check_cmd->args);
    else if(ft_strncmp(check_cmd->command, "echo", 5) == 0)
        result = ft_echo_built_in(data, check_cmd->args);
    else if(ft_strncmp(check_cmd->command, "env", 4) == 0)
        result = ft_env_built_in(data, check_cmd->args);
    else if(ft_strncmp(check_cmd->command, "export", 7) == 0)
        result = ft_export_built_in(data, check_cmd->args);
    else if(ft_strncmp(check_cmd->command, "pwd", 4) == 0)
        result = ft_pwd_built_in(data, check_cmd->args);
    else if(ft_strncmp(check_cmd->command, "unset", 6) == 0)
        {
            result = ft_unset_built_in(data, check_cmd->args);
        }
    // else if(ft_strncmp(check_cmd->command, "exit", 5) == 0) // --> exit built in to be made
    //     result = ft_pwd_built_in(data, check_cmd->args);
    return(result);
}

static int execute_system_binaries(t_data *data, t_cmd *cmd)
{
    // Add the following debug print statement
    fprintf(stderr, "Inside execute_system_binaries function...\n");
    // End of debug print statement

    if(!cmd->command || cmd->command[0] == '\0')
        return(COMMAND_NOT_FOUND);
    // here_doc(cmd->args);
    if(cmd_is_dir(cmd->command))
        return (COMMAND_NOT_FOUND);
    cmd->path = fetch_command_path(data, cmd->command);
    if(!cmd->path)
        return (COMMAND_NOT_FOUND);
    if(execve(cmd->path, cmd->args, data->env) == -1)
        error_msg_commad("execve: ", NULL, strerror(errno), errno);
    return (EXIT_FAILURE);
}


static int execute_local_bin(t_data *data, t_cmd *cmd)
{
    int result; 
    printf("Inside execute_local_bin function...\n");
    printf("cmd->path: %s\n", cmd->path);

    result = check_command_not_found(data, cmd);
    if(result != 0)
        return (result);
    if(execve(cmd->path, cmd->args, data->env) == -1)
        error_msg_commad("execve: ", NULL, strerror(errno), errno);
    return (EXIT_FAILURE);
}

char **remove_heredoc_args(char **args)
{
    char **new_args;
    int i, j;

    i = 0;
    while (args[i] != NULL)
        i++;

    new_args = (char **)malloc((i + 1) * sizeof(char *));
    i = 0;
    j = 0;

    while (args[i] != NULL)
    {
        if (ft_strcmp(args[i], "<<") != 0 && (i == 0 || ft_strcmp(args[i - 1], "<<") != 0))
        {
            new_args[j] = args[i];
            j++;
        }
        i++;
    }
    new_args[j] = NULL;

    return new_args;
}

int execute_commands(t_data *data, t_cmd *cmd)
{
    int ret;
    printf(COLOR_GREEN " ~~~~~~ Entered the executeve commands ~~~~~~~~\n");

    // if (!check_here_doc(cmd->args))
    //     {
    //         here_doc(cmd->args);
    //         cmd->args = remove_heredoc_args(cmd->args);
    //     }
    
    redirect_io(cmd->io_fds);
    set_pipe_fds(data->cmd_lst, cmd);
    close_fds(data->cmd_lst, false);

    fprintf(stderr, "cmd->command: %s\n", cmd->command);
    fprintf(stderr, "ft_strchr result: %p\n", ft_strchr(cmd->command, '/'));

    ret = execute_built_ins(data, cmd);
    if (ret != COMMAND_NOT_FOUND)
        exit(ret); 
    if (ft_strchr(cmd->command, '/') == NULL)
        ret = execute_system_binaries(data, cmd);
    else
        cmd->path = cmd->command;
    ret = execute_local_bin(data, cmd);

    fprintf(stderr, " ~~~~~~ Leaving the executeve commands ~~~~~~~~\n" COLOR_RESET);
    return (ret);
}





