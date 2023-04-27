#include "../../inc/minishell.h"


static char *find_valid_path_command(char *cmd, char **paths)
{
    int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
        cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			error_msg_commad("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

static char **fetch_paths_from_env(t_data *data)
{
    char **env_path;

    if(fetch_env_variable_index(data->env, "PATH") == -1)
        return (NULL);
    env_path = ft_split(fetch_env_variable_char(data->env, "PATH"), ':');
    if(!env_path)
        return (NULL);
    return (env_path);
}

char *fetch_command_path(t_data *data, char *name)
{
    char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
    env_paths = fetch_paths_from_env(data);
    if(!env_paths)
        return (NULL);
    cmd = ft_strjoin("/", name);
    if(!cmd)
    {
        free_str_tab(env_paths);
        return (NULL);
    }
    cmd_path = find_valid_path_command(cmd, env_paths);
    if(!cmd_path)
    {
        free_ptr(cmd);
        free_str_tab(env_paths);
        return (NULL);
    }
    return (cmd_path);
}