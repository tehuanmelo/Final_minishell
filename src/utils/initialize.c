#include "../../inc/minishell.h"


/* init_env:
*	Initializes a data variable with the contents of the environment
*	variables inherited from the original shell.
*	Returns 0 on failure, 1 on success.
*/
static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(count_env_variables(env) + 1, sizeof * data->env);
	if (!data->env)
		return (false);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (false);
		i++;
	}
	return (true);
}

/* init_wds:
*	Initializes working directory variables as a safeguard against
*	environment PWD and OLDPWD being unset or otherwise not present
*	in the environment. Used for cd builtin.
*	Returns true if successful, false in case of error.
*/
static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->current_dir = ft_strdup(wd);
	if (!data->current_dir)
		return (false);
	if (fetch_env_variable_index(data->env, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(fetch_env_variable_char(data->env,
					"OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(wd);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

/* init_data:
*	Initializes the data structure used in parsing and executing user input.
*	Returns true if successful, false in case of error.
*/
bool	init_data(t_data *data, char **env)
{
	if (!init_env(data, env))
	{
		error_msg_commad("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		error_msg_commad("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	// data->tokens = NULL;
	// data->input = NULL;
	// data->cmd_lst = NULL;
	data->pid = -1;
	data->exit_code= 0;
	return (true);
}

/* init_io:
*	Initializes a structure with default values to contain
*	infile and outfile information for a command.
*/
void	init_io(t_cmd *cmd)
{
		cmd->io_fds = malloc(sizeof(t_io_fds));
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
}