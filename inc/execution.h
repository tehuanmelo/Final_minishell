// #ifndef EXECUTION_H
// #define EXECUTION_H

// #include "minishell.h"
// #include "parsing.h"

// #ifndef PATH_MAX
// #define PATH_MAX 4096
// #endif

// #define COMMAND_NOT_FOUND 127
// #define COMMAND_NOT_EXECUTABLE 126


// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ Initialization ~~~~~~~~~~~~~
// //# ----------------------------------------------
// bool	init_data(t_data *data, char **env);
// void	init_io(t_cmd *cmd);


// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ BUILTS INS ~~~~~~~~~~~~~
// //# ----------------------------------------------
// int ft_cd_built_in(t_data *data, char **args);
// int	ft_echo_built_in(t_data *data, char **args);
// int	ft_env_built_in(t_data *data, char **args);
// int ft_export_built_in(t_data *data, char **args);
// int ft_pwd_built_in(t_data *data, char **args);
// int ft_unset_built_in(t_data *data, char **args); 

// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ ENV MANIPUlATION ~~~~~~~~~~~~~
// //# ----------------------------------------------
// int     count_env_variables(char **env);
// char    *fetch_env_variable_char(char **env, char *var);
// int     fetch_env_variable_index(char **env, char *var);
// bool    create_the_new_env_var(t_data *data, 
//         char *env_key, char *value);
// bool    check_for_the_env_key(char *var);
// bool    delete_the_env_variables(t_data *data, int index);


// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ PIPES ~~~~~~~~~~~~~
// //# ----------------------------------------------
// bool	cmd_is_dir(char *cmd);
// char    *fetch_command_path(t_data *data, char *name);
// int	    check_command_not_found(t_data *data, t_cmd *cmd);
// bool	set_pipe_fds(t_cmd *cmds, t_cmd *c);
// bool	create_pipes(t_data *data);

// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ REDIRECTIONS ~~~~~~~~~~~~~
// //# ----------------------------------------------
// bool	restore_io(t_io_fds *io);
// bool	check_infile_outfile(t_io_fds *io);
// bool	set_pipe_fds(t_cmd *cmds, t_cmd *c);
// bool	redirect_io(t_io_fds *io);

// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ EXECUTION ~~~~~~~~~~~~~
// //# ----------------------------------------------
// int     execute_built_ins(t_data *data, t_cmd *check_cmd);
// int     execute_commands(t_data *data, t_cmd *cmd);
// int	    execute(t_data *data);


// //# ----------------------------------------------
// //# ~~~~~~~~~~~~~ FREES & CLEANUPS ~~~~~~~~~~~~~
// //# ----------------------------------------------
// int	    error_msg_commad(char *command, char *detail, 
//         char *error_message, int error_nb);
// void	free_ptr(void *ptr);
// void	free_str_tab(char **tab);
// void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
// void	close_fds(t_cmd *cmds, bool close_backups);
// void	exit_shell(t_data *data, int exno);


// #endif