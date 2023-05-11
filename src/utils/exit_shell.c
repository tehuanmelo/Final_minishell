#include "../../inc/minishell.h"


/* exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.
*/
void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd_lst && data->cmd_lst->io_fds)
			close_fds(data->cmd_lst, true);
		free_data(data, data->cmd_lst, true);
		free_commands(data->cmd_lst);
		free_tokens_list(data->tokens);
	}
	exit(exno);
}

void	exit_shell2(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd_lst && data->cmd_lst->io_fds)
			close_fds(data->cmd_lst, true);
		free_data(data, data->cmd_lst, true);
		free_commands2(data->cmd_lst);
		free_tokens_list(data->tokens);
	}
	exit(exno);
}