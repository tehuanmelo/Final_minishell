#include "../../inc/minishell.h"

t_data data;

int is_redirection_operator(const char *s)
{
    return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<") == 0);
}


int handle_outfile_redirection(t_cmd *cmd, int index)
{
    int open_flag = O_WRONLY | O_CREAT;

    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return (COMMAND_NOT_FOUND);

    if (ft_strcmp(cmd->args[index], ">") == 0)
    {
        open_flag |= O_TRUNC;
    }
    else if (ft_strcmp(cmd->args[index], ">>") == 0)
    {
        open_flag |= O_APPEND;
    }

    close(cmd->io_fds->fd_out);
    cmd->io_fds->fd_out = open(cmd->args[index + 1], open_flag, 0644);
    
    if (cmd->io_fds->fd_out == -1)
    {
        data.exit_code = error_msg_commad(cmd->args[index], NULL, strerror(errno), 1);
        return (data.exit_code);
    }

    if (cmd->args[index + 2] != NULL && !is_redirection_operator(cmd->args[index + 2]))
    {
        write(cmd->io_fds->fd_out, cmd->args[index + 2], ft_strlen(cmd->args[index + 2]));
        free(cmd->args[index + 2]);
        cmd->args[index + 2] = NULL;
    }

    free(cmd->args[index]);
    cmd->args[index] = NULL;

    return (EXIT_SUCCESS);
}


char *remove_double_quotes(const char *str)
{
    if (!str)
        return NULL;

    size_t len = ft_strlen(str);
    if (len < 2)
        return ft_strdup(str);

    if (str[0] == '\"' && str[len - 1] == '\"')
    {
        char *new_str = ft_substr(str, 1, len - 2);
        return new_str;
    }
    return ft_strdup(str);
}
    

int handle_infile_redirection(t_cmd *cmd, int index)
{
    if (!cmd || !cmd->args || !cmd->io_fds || index < 0)
        return (COMMAND_NOT_FOUND);

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

    while (cmd->args[i])
    {
        if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
        {
            if (handle_outfile_redirection(cmd, i) != EXIT_SUCCESS)
            {
                error_occurred = 1;
                break;
            }
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

    return error_occurred;
}

