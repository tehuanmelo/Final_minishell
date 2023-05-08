#include "../../inc/minishell.h"



int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

/* update_the_env_dir
# @brief: 
* Updates the cd directory in the enviornment containing both the OLDPWD and the PWD path
# @example: 
* This updates the oldpwd directory as well as the pwd directory
*/
static void update_the_env_dir(t_data *data, char *env_dir)
{
    create_the_new_env_var(data, "OLDPWD", fetch_env_variable_char(data->env, "PWD"));
    create_the_new_env_var(data, "PWD", env_dir);
    if(data->old_working_dir)
    {
        free_ptr(data->old_working_dir);
        data->old_working_dir = ft_strdup(data->current_dir);
    }
    if(data->current_dir)
    {
        free_ptr(data->current_dir);
        data->current_dir = ft_strdup(env_dir);
    }
    free_ptr(env_dir);
}

/* chdir_error_call
# @brief: 
*  
*/
static bool chdir_error_call(char *path)
{
    if (errno == ESTALE)
        errno = ENOENT;
    error_msg_commad("cd", path, strerror(errno), errno);
    return (false);
}

/* 
# @brief: 
*/
static bool change_dir(t_data *data, char *path)
{

    char *ret;
    char *tmp;
    char cwd[PATH_MAX];

    ret = NULL;
    if(chdir(path) != 0)
        return (chdir_error_call(path));
    ret = getcwd(cwd, PATH_MAX);
    if(!ret)
    {
        error_msg_commad(COLOR_RED "cd: error in retrieving current directory", "getcwd: unable to access the parent directories" COLOR_RESET, strerror(errno), errno);
        ret = ft_strjoin(data->current_dir, "/");
        tmp = ret; 
        ret = ft_strjoin(tmp, path);
        free_ptr(tmp);
    }
    else
        ret = ft_strdup(cwd);
    update_the_env_dir(data, ret);
    return (true);
}

/*
*/
int ft_cd_built_in(t_data *data, char **args)
{
    char    *path;
    if(!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
    {
        path = fetch_env_variable_char(data->env, "HOME");
        if (!path || *path == '\0' || ft_isspace(*path))
            return(error_msg_commad("cd", NULL, "Home not set", EXIT_FAILURE));
        return(!change_dir(data, path));
    }
    if(args[2])
        return(error_msg_commad("cd", NULL, "too many arguments", EXIT_FAILURE));
    if(strncmp(args[1], "-", 2) == 0)
    {
        path = fetch_env_variable_char(data->env, "OLDPWD");
        if(!path)
            return(error_msg_commad("cd", NULL, "OldPwd not set", EXIT_FAILURE));
        return(!change_dir(data, path));
    }
    return (!change_dir(data, args[1]));
}   