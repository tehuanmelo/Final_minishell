#include "../../inc/minishell.h"


static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd_lst, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

/* create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.
*/
static int	create_children(t_data *data)
{
	fprintf(stderr, "Create Children\n");
	t_cmd	*cmd;

	cmd = data->cmd_lst;
	while (data->pid != 0 && cmd)
	{
		printf("Starting the fork process\n");
		data->pid = fork();
		if (data->pid == -1)
			return (error_msg_commad("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0){
            printf("Inside create_children, calling execute_commands...\n"); // Add this line
			execute_commands(data, cmd);
        }
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* prep_for_exec:
*	Prepares the command list for execution, creates pipes
*	and checks the input and output files.
*	Returns false in case of error, true if all is ready to
*	execute.
*/
static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd_lst)
	{
		// printf("Inside prep_for_exec: No data or cmd_lst\n");
		return (EXIT_SUCCESS);
	}
	if (!data->cmd_lst->command)
	{
		// printf("Inside prep_for_exec: No command\n");
		if (data->cmd_lst->io_fds && !check_infile_outfile(data->cmd_lst->io_fds))
		{
			// printf("Inside prep_for_exec: IO Error\n");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
	{
		printf("Inside prep_for_exec: Pipe creation failure\n");
		return (EXIT_FAILURE);
	}
	printf("Inside prep_for_exec: COMMAND_NOT_FOUND case\n");
	return (COMMAND_NOT_FOUND);
}

/* execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.
*/
int execute(t_data *data)
{
    int ret;

    ret = prep_for_exec(data);
    if (ret != COMMAND_NOT_FOUND) {
        // printf("Inside execute: Non-command case...\n");
        return (ret);
    }

    if (!data->cmd_lst->next && !data->cmd_lst->prev
        && check_infile_outfile(data->cmd_lst->io_fds))
    {
        printf("Inside execute: Built-in command case...\n");
        redirect_io(data->cmd_lst->io_fds);
        ret = execute_built_ins(data, data->cmd_lst);
        restore_io(data->cmd_lst->io_fds);

        if (ret != COMMAND_NOT_FOUND) {
            printf("Returning from built-in command case...\n");
            return (ret);
        }
    }

    printf("Inside execute: create_children case...\n");
		ret = create_children(data);

    // Add the following line to restore standard input and output after executing the last command in the pipeline
    restore_io(data->cmd_lst->io_fds);

	if (data->cmd_lst->io_fds->fd_in != STDIN_FILENO)
		close(data->cmd_lst->io_fds->fd_in);
	if (data->cmd_lst->io_fds->fd_out != STDOUT_FILENO)
		close(data->cmd_lst->io_fds->fd_out);
    return (ret);
}




