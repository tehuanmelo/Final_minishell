/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:27:07 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/04/25 22:00:21 by tehuanmelo       ###   ########.fr       */
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
