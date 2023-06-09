/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:03:35 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/25 19:02:23 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN "\033[36m"
# define COLOR_RESET "\033[0m"

# include "../src/libft/inc/libft.h"
# include <errno.h>
# include <execinfo.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MINI_PROMPT "\033[34;47;1;3mminishell\033[36;49;1;3m ~> \033[0m"
# define HD_PROMPT "\033[33;49;3mheredoc~> \033[0m"

enum				e_type
{
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	ENV = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC = 222,
	DREDIR_OUT,
	EMPTY,
	WORD,
	EXIT_STATUS,
};

enum				e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct s_io_fds
{
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	int				stdin_backup;
	int				stdout_backup;
}					t_io_fds;

typedef struct s_cmd
{
	char			**args;
	char			*command;
	char			*path;
	int				pipe_fd[2];
	t_io_fds		*io_fds;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*input;
	int				nb_cmd;
	int				exit_code;
	int				command_index;
	char			**env;
	char			*current_dir;
	char			*old_working_dir;
	int				heredoc_fd;
	bool			heredoc_call;
	t_elem			*tokens;
	t_cmd			*cmd_lst;
	pid_t			pid;
}					t_data;

extern t_data		g_data;

// -------------- minishell --------------
void				set_data(t_data *data, char *str);
void				init_shell(t_data *data);
int					_readline_(char **input);

// #######################################
//               LEXER-DIR
// #######################################

// --------------- lexer -----------------
t_elem				*get_tokens_list(char *input);
void				check_quotes_flag(char input, int *d_quotes_flag,
						int *s_quotes_flag);
int					get_str_length(char *input);
int					is_env(char *input);
int					check_state(int d, int s);

// ----------- sintax error --------------
int					sintax_error(t_data *data);
int					is_in_quotes(enum e_state state);
int					is_redir(enum e_type type);
int					is_quote(enum e_type type);
int					is_pipe(enum e_type type);
void				syntax_error_message(char *str);
t_elem				*get_list_prev_bound(t_elem *tokens);
t_elem				*get_list_next_bound(t_elem *tokens);

// ------------ free list ----------------
void				free_tokens_list(t_elem *tokens);
char				**remove_heredoc_args(char **args);
int					is_redirection_operator(const char *s);
int					handle_outfile_utils(t_cmd *cmd, int index);

// ------------- expansions --------------
void				expand_env(t_data *data);

// #######################################
//              PARSER-DIR
// #######################################

// -------------- parser -----------------
t_cmd				*parser(t_data *data);
t_cmd				*new_command(void);

// ------------ parser_utils -------------
int					count_args(t_elem **head);
int					count_commands(t_data *data);
void				append_command(t_cmd **head, t_cmd *new);
void				free_commands(t_cmd *cmds);
int					parse_redirection(t_cmd *cmd);
char				*join_string(char *s1, char *s2);
int					check_if_is_redir(char *content);
int					handle_outfile_utils(t_cmd *cmd, int index);
int					infile_call(t_cmd *cmd, int index);

// ------------- here-doc ---------------
int					check_here_doc(char **args);
char				**remove_heredoc_args(char **args);
void				here_doc(char **args, int should_print, int command_index);
void				print_file_contents(const char *filename);
int					check_here_doc(char **args);
char				**get_delimiter(char **input, int nbr_heredocs);
void				checking_delimiter_index(int *nbr_heredocs, int *i,
						char **delimiter, char *line);
void				free_delimiter(char **delimiter);
int					get_heredoc_nbr(char **args);

// #######################################
//              SIGNALS-DIR
// #######################################

// -------------- signals ----------------
void				init_signals(void);
void				sigint_handler(int sig);
void				sigint_handler_heredoc(int sig);

// #######################################
// ************* DELETE-ME ***************
// #######################################
void				print_tokens(t_elem *list);
void				print_comands(void);
void				print_t_cmd(t_cmd *cmd);

//----------------EXECUTION
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126

void				print_t_data(t_data *data);
void				print_env_variables(char **env);

//# ----------------------------------------------
//# ~~~~~~~~~~~~~ Initialization ~~~~~~~~~~~~~
//# ----------------------------------------------
bool				init_data(t_data *data, char **env);
void				init_io(t_cmd *cmd);

//# ----------------------------------------------
//# ~~~~~~~~~~~~~ BUILTS INS ~~~~~~~~~~~~~
//# ----------------------------------------------
int					ft_cd_built_in(t_data *data, char **args);
int					ft_echo_built_in(t_data *data, char **args);
int					ft_env_built_in(t_data *data, char **args);
int					ft_export_built_in(t_data *data, char **args);
int					ft_pwd_built_in(t_data *data, char **args);
int					ft_unset_built_in(t_data *data, char **args);
int					ft_exit_built_in(t_data *data, char **args);
void				close_fd(void);
//# ----------------------------------------------
//# ~~~~~~~~~~~~~ ENV MANIPUlATION ~~~~~~~~~~~~~
//# ----------------------------------------------
int					count_env_variables(char **env);
char				*fetch_env_variable_char(char **env, char *var);
int					fetch_env_variable_index(char **env, char *var);
bool				create_the_new_env_var(t_data *data,
						char *env_key, char *value);
bool				check_for_the_env_key(char *var);
bool				delete_the_env_variables(t_data *data, int index);

//# ----------------------------------------------
//# ~~~~~~~~~~~~~ PIPES ~~~~~~~~~~~~~
//# ----------------------------------------------
bool				cmd_is_dir(char *cmd);
char				*fetch_command_path(t_data *data, char *name);
int					check_command_not_found(t_data *data, t_cmd *cmd);
bool				set_pipe_fds(t_cmd *cmds, t_cmd *c);
bool				create_pipes(t_data *data);

//# ----------------------------------------------
//# ~~~~~~~~~~~~~ REDIRECTIONS ~~~~~~~~~~~~~
//# ----------------------------------------------
bool				restore_io(t_io_fds *io);
bool				check_infile_outfile(t_io_fds *io);
bool				set_pipe_fds(t_cmd *cmds, t_cmd *c);
bool				redirect_io(t_io_fds *io, int command_index);
bool				main_redirect_io(t_io_fds *io);
//# ----------------------------------------------
//# ~~~~~~~~~~~~~ EXECUTION ~~~~~~~~~~~~~
//# ----------------------------------------------
int					execute_built_ins(t_data *data, t_cmd *check_cmd);
int					execute_commands(t_data *data, t_cmd *cmd,
						int command_index);
int					execute(t_data *data);
char				**remove_heredoc_args(char **args);

//# ----------------------------------------------
//# ~~~~~~~~~~~~~ FREES & CLEANUPS ~~~~~~~~~~~~~
//# ----------------------------------------------
int					error_msg_commad(char *command, char *detail,
						char *error_message, int error_nb);
void				free_ptr(void *ptr);
void				free_data(t_data *data, t_cmd *cmds, bool flag);
void				free_str_tab(char **tab);
void				close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void				close_fds(t_cmd *cmds, bool close_backups);
void				close_child_fds(t_cmd *cmds);
void				*free_io(t_io_fds *io);
void				close_parent_fds(t_cmd *cmds);
void				exit_shell(t_data *data, int exno);
void				free_commands2(t_cmd *cmds);
void				exit_shell2(t_data *data, int exno);
void				exit_shell3(t_data *data, int exno);
void				lstclear_token(t_elem **lst, void (*del)(void *));
void				free_commands_0(t_cmd *cmds);
void				free_heredoc_args(char **args, int i);
#endif
