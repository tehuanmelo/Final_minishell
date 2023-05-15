/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:05:22 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/15 13:36:23 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_env(char *input)
{
	if (ft_strlen(input) > 1)
	{
		if (ft_isalpha(*(++input)) || *input == '_' || *input == '?')
			return (ENV);
	}
	return (0);
}

void	check_quotes_flag(char input, int *d_quotes_flag, int *s_quotes_flag)
{
	if (input == D_QUOTE && *s_quotes_flag == -1)
		*d_quotes_flag *= -1;
	else if (input == S_QUOTE && *d_quotes_flag == -1)
		*s_quotes_flag *= -1;
}

int	get_env_len(char *input, int len)
{
	len++;
	if (input[len] == '?')
		return (++len);
	else if (!ft_isalpha(input[len]) && input[len] != '_')
		return (len);
	else
	{
		while (ft_isalnum(input[len]) || input[len] == '_')
			len++;
	}
	return (len);
}

int	get_redir_len(char *input, int len)
{
	len++;
	if (is_redir(input[len]))
		return (++len);
	return (len);
}

int	get_str_length(char *input)
{
	int	len;

	len = 0;
	if (*input == WHITE_SPACE || *input == D_QUOTE || *input == S_QUOTE
		|| *input == PIPE)
		len = 1;
	else if (input[len] == ENV)
		len = get_env_len(input, len);
	else if (is_redir(input[len]))
		len = get_redir_len(input, len);
	else
	{
		while (input[len] && input[len] != ENV && input[len] != WHITE_SPACE
			&& input[len] != PIPE && !is_quote(input[len])
			&& !is_redir(input[len]))
			len++;
	}
	return (len);
}
