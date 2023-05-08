#include "../../inc/minishell.h"

t_data data;

int is_redirection_operator(const char *s)
{
    return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<") == 0);
}


// int is_redirection_operator(const char *s)
// {
//     return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<") == 0);
// }

int handle_outfile_redirection(t_cmd *cmd, int index)
{
    int open_flag;

    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return (COMMAND_NOT_FOUND);

    if (cmd->args[index + 1] == NULL)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (EXIT_FAILURE);
    }

    open_flag = (ft_strcmp(cmd->args[index], ">>") == 0) ? O_APPEND : O_TRUNC;
    close(cmd->io_fds->fd_out);
    cmd->io_fds->fd_out = open(cmd->args[index + 1], O_WRONLY | O_CREAT | open_flag, 0644);
    if (cmd->io_fds->fd_out == -1)
    {
        data.exit_code = error_msg_commad(cmd->args[index], NULL, strerror(errno), 1);
        return (data.exit_code);
    }

    if (cmd->args[index + 2] != NULL)
    {
        write(cmd->io_fds->fd_out, cmd->args[index + 2], ft_strlen(cmd->args[index + 2]));
        free(cmd->args[index + 2]);
        cmd->args[index + 2] = NULL;
    }

    free(cmd->args[index]);
    cmd->args[index] = NULL;
    // free(cmd->args[index + 1]);
    // cmd->args[index + 1] = NULL;

    return (EXIT_SUCCESS);
}


int handle_infile_redirection(t_cmd *cmd, int index)
{
    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return (COMMAND_NOT_FOUND);
    // if (cmd->args[index + 1] == NULL)
    // {
    //     printf("minishell: syntax error near unexpected token `newline'\n");
    //     return (EXIT_FAILURE);
    // }
    close(cmd->io_fds->fd_out);
    data.redirection_infile = true;
    cmd->io_fds->fd_in = open(cmd->args[index + 1], O_RDONLY);
    if (cmd->io_fds->fd_in == -1)
    {
        char *missing_filename = ft_strdup(cmd->args[index + 1]);
        for (int i = 0; cmd->args[i] != NULL; i++)
        {
            free(cmd->args[i]);
            cmd->args[i] = NULL;
        }
        data.exit_code = error_msg_commad(missing_filename, NULL, strerror(errno), 1);
        free(missing_filename);
        return (data.exit_code);
    }
    free(cmd->args[index]);
    cmd->args[index] = NULL;
    return (EXIT_SUCCESS);
}
int parse_redirection(t_cmd *cmd)
{
    int i = 0;
    int error_occurred = 0;
    int last_redirection_operator = -1;
    int redirection_count = 0;

    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
        {
            last_redirection_operator = i;
            redirection_count++;
        }
        else if (ft_strcmp(cmd->args[i], "<") == 0)
        {
            if (handle_infile_redirection(cmd, i) != EXIT_SUCCESS)
            {
                error_occurred = 1;
                break;
            }
        }
        i++;
    }

    if (last_redirection_operator != -1)
    {
        if (handle_outfile_redirection(cmd, last_redirection_operator) != EXIT_SUCCESS)
        {
            error_occurred = 1;
        }
    }

    if (redirection_count > 1)
    {
        for (i = 0; cmd->args[i]; i++)
        {
            if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
            {
                free(cmd->args[i]);
                cmd->args[i] = NULL;
            }
        }
    }

    return error_occurred;
}
