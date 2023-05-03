NAME = minishell

LEXER = lexer.c lexer_utils.c sintax_error.c sintax_error_utils.c expansion.c utils.c print_tokens_delete_me.c
PARSER = parser.c parser_utils.c here_doc.c parse_redirections.c print_commands_delete_me.c
SIGNALS = signals.c
BUILT_INS = cd.c echo.c env.c export.c pwd.c unset.c exit.c
EXECUTION = env_variable.c execute_command.c executives_utils.c main_execution.c our_env_var.c path_finder.c
REDPI = file_input_output.c pipes.c
DEBUGGER = debugger_print.c
UTILS =  clean.c error.c exit_shell.c initialize.c 
MAIN = main.c  minishell.c 

CC = gcc
# CFLAGS = -Wall -Werror -Wextra -I/usr/local/cellar/readline/8.1/include
# READLINE_LIB =  -L/usr/local/cellar/readline/8.1/lib -lreadline
CFLAGS = -Wall -Werror -Wextra -I/usr/local/cellar/readline/8.1.1/include
READLINE_LIB =  -L/usr/local/cellar/readline/8.1.1/lib -lreadline
# CFLAGS = -Wall -Werror -Wextra -I/opt/homebrew/Cellar/readline/8.2.1/include
# READLINE_LIB =  -L/opt/homebrew/Cellar/readline/8.2.1/lib -lreadline
# CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
OBJPATH = ./obj/
LIBFT = ./src/libft

SRC = 	$(addprefix src/lexer/, $(LEXER)) \
		$(addprefix src/parser/, $(PARSER)) \
		$(addprefix src/built_ins/, $(BUILT_INS)) \
		$(addprefix src/RedPi/, $(REDPI)) \
		$(addprefix src/execution/, $(EXECUTION)) \
		$(addprefix src/debugger/, $(DEBUGGER)) \
		$(addprefix src/utils/, $(UTILS)) \
		$(addprefix src/signals/, $(SIGNALS)) \
		$(addprefix src/, $(MAIN)) \

OBJ = 	$(addprefix $(OBJPATH), $(PARSER:.c=.o)) \
		$(addprefix $(OBJPATH), $(LEXER:.c=.o)) \
		$(addprefix $(OBJPATH), $(SIGNALS:.c=.o)) \
		$(addprefix $(OBJPATH), $(BUILT_INS:.c=.o)) \
		$(addprefix $(OBJPATH), $(DEBUGGER:.c=.o)) \
		$(addprefix $(OBJPATH), $(EXECUTION:.c=.o)) \
		$(addprefix $(OBJPATH), $(REDPI:.c=.o)) \
		$(addprefix $(OBJPATH), $(UTILS:.c=.o)) \
		$(addprefix $(OBJPATH), $(MAIN:.c=.o)) \

.SILENT:

all:	$(MAKELIBFT) $(OBJPATH) $(NAME)

$(MAKELIBFT):
	cd $(LIBFT) && $(MAKE)

$(OBJPATH):
	mkdir $(OBJPATH)

$(NAME):	$(OBJ)
	cd $(LIBFT) && $(MAKE)	
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT)/libft.a $(READLINE_LIB)
	echo "\033[30;43;1;3mCompilation done successfully!\033[0m"


$(OBJPATH)%.o:	src/lexer/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/parser/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/signals/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/built_ins/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/debugger/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/execution/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/RedPi/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/utils/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o:	src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJPATH)
	cd $(LIBFT) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT) && $(MAKE) fclean

re:		fclean all