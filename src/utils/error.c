#include "../../inc/minishell.h"


/* ft_join_string
* Joins two strings, freeing the previous string. 
* Returns the new concatenated string. 
*/
char *ft_join_string(char *str, char *add)
{
    char *temp;
    if(!add)
        return (str);
    if(!str)
        return(ft_strdup(add));
    temp = str;
    str = ft_strjoin(temp, add);
    free_ptr(temp);
    return (str);
}

static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

int	error_msg_commad(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL && command[0] != '\0') // Check if command is not empty
	{
		msg = ft_join_string(msg, command);
		msg = ft_join_string(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = ft_join_string(msg, "`");
		msg = ft_join_string(msg, detail);
		if (detail_quotes)
			msg = ft_join_string(msg, "'");
		msg = ft_join_string(msg, ": ");
	}
	msg = ft_join_string(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (error_nb);
}


void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = ft_join_string(msg, errmsg);
	if (quotes)
		msg = ft_join_string(msg, " `");
	else
		msg = ft_join_string(msg, ": ");
	msg = ft_join_string(msg, detail);
	if (quotes)
		msg = ft_join_string(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}

/* usage_message:
*	Prints a usage message. Used if start-up arguments are invalid.
*/
bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
