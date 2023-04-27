// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.h                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/04/16 10:10:35 by tehuanmelo        #+#    #+#             */
// /*   Updated: 2023/04/27 12:30:24 by tde-melo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef PARSING_P
// #define PARSING_P

// #include "minishell.h"

// #define MINI_PROMPT "\033[36;47;1mminishell\033[36;49;1m ➡️ \033[0m"


// enum e_type
// {
//     WHITE_SPACE = ' ',
//     NEW_LINE = '\n',
//     S_QUOTE = '\'',
//     D_QUOTE = '\"',
//     ENV = '$',
//     PIPE = '|',
//     REDIR_IN = '<',
//     REDIR_OUT = '>',
//     HERE_DOC = 222,
//     DREDIR_OUT,
//     EMPTY,
//     WORD,
// };

// enum e_state
// {
//     IN_DQUOTE,
//     IN_QUOTE,
//     GENERAL,
// };

// typedef struct s_elem
// {
//     char *content;
//     // char *content_backup;
//     int len;
//     enum e_type type;
//     enum e_state state;
//     struct s_elem *next;
//     struct s_elem *prev;
// } t_elem;




// // -------------- minishell --------------
// void	set_data(char *str);
// void init_shell();
// int _readline_(char **input);

// // #######################################
// //               LEXER-DIR
// // #######################################

// // --------------- lexer -----------------
// t_elem *get_tokens_list(char *input);
// void check_quotes_flag(char input, int *d_quotes_flag, int *s_quotes_flag);
// int get_str_length(char *input);
// int is_env(char *input);
// int check_state(int d, int s);

// // ----------- sintax error --------------
// int sintax_error();
// int is_in_quotes(enum e_state state);
// int is_redir(enum e_type type);
// int is_quote(enum e_type type);
// int is_pipe(enum e_type type);

// // ------------ free list ----------------
// void free_tokens_list(t_elem *tokens);

// // ------------- expansions --------------
// void expand_env();

// // #######################################
// //              PARSER-DIR
// // #######################################

// // -------------- parser -----------------
// t_cmd *parser();

// // ------------ parser_utils -------------
// int count_args(t_elem **head);
// int count_commands();
// void append_command(t_cmd **head, t_cmd *new);
// t_cmd *new_command();
// void parse_redirection(t_cmd *cmd);

// // ------------- here-doc ---------------
// int check_here_doc(char **args);
// void here_doc(char **input);

// // #######################################
// //              SIGNALS-DIR
// // #######################################

// // -------------- signals ----------------
// void    init_signals();
// void	handle_sigint(int sig);

// // #######################################
// // ************* DELETE-ME ***************
// // #######################################
// void print_tokens(t_elem *list);
// void print_comands();


// #endif