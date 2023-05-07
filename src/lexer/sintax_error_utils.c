/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:27:07 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/07 12:54:24 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	is_redir(enum e_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == DREDIR_OUT
		|| type == HERE_DOC);
}

int	is_quote(enum e_type type)
{
	return (type == D_QUOTE || type == S_QUOTE);
}

int	is_in_quotes(enum e_state state)
{
	return (state == IN_DQUOTE || state == IN_QUOTE);
}

int	is_pipe(enum e_type type)
{
	return (type == PIPE);
}

void syntax_error_message(char *str)
{
	data.exit_code = 258;
	ft_putstr("minishell: syntax error near unexpected token ");
	if (!ft_strcmp(str, "|"))
		ft_putstr("`|'\n");
	else if (!ft_strcmp(str, ">"))
		ft_putstr("`>'\n");
	else if (!ft_strcmp(str, "<"))
		ft_putstr("`<'\n");
	else if (!ft_strcmp(str, ">>"))
		ft_putstr("`>>'\n");
	else 
		ft_putstr("`<<'\n");
}
