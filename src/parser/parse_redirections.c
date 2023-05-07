#include "../../inc/minishell.h"

t_data data;

void handle_outfile_redirection(t_cmd *cmd, int index)
{
    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return;

    if (cmd->args[index + 1] == NULL)
    {
        // Handle missing file name after '>' or '>>'
        printf("minishell: syntax error near unexpected token `newline'\n");
        return;
    }

    int flags = O_WRONLY | O_CREAT;
    if (ft_strcmp(cmd->args[index], ">>") == 0)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;

    cmd->io_fds->fd_out = open(cmd->args[index + 1], flags, 0644);
    if (cmd->io_fds->fd_out == -1)
        perror("minishell");
    //frprintf(stderr, "Fds_outptut --->  %d\n", cmd->io_fds->fd_out);
    // Remove the redirection operator and file name from args
    free(cmd->args[index]);
    // free(cmd->args[index + 1]);
    cmd->args[index] = NULL;
    // cmd->args[index + 1] = NULL;
}

int handle_infile_redirection(t_cmd *cmd, int index)
{
    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return (COMMAND_NOT_FOUND);

    if (cmd->args[index + 1] == NULL)
    {
        // Handle missing file name after '<'
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (EXIT_FAILURE);
    }
    close(cmd->io_fds->fd_out);
    cmd->io_fds->fd_in = open(cmd->args[index + 1], O_RDONLY);
    if (cmd->io_fds->fd_in == -1)
    {
        // Save the cmd->args[index] value
        char *arg_index = strdup(cmd->args[index]);

        // Free and remove all the args
        for (int i = 0; cmd->args[i] != NULL; i++)
        {
            free(cmd->args[i]);
            cmd->args[i] = NULL;
        }

        // Call the error_msg_commad function with the saved arg_index value
        data.exit_code =error_msg_commad(arg_index, NULL, strerror(errno), 1);

        // Free the arg_index value
        free(arg_index);

        return (data.exit_code);
    }
    free(cmd->args[index]);
    cmd->args[index] = NULL;
    return (EXIT_SUCCESS);
}


void parse_redirection(t_cmd *cmd)
{
    if (!cmd || !cmd->args)
        return;

    int i = 0;

    while (cmd->args[i]) 
    {
        // printf("commands ---> %s\n", cmd->args[i]);
        if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
            handle_outfile_redirection(cmd, i);
        else if (strcmp(cmd->args[i], "<") == 0) 
            data.exit_code = handle_infile_redirection(cmd, i);
        if (data.exit_code != EXIT_SUCCESS)
            return;
        i++;
    }
}
