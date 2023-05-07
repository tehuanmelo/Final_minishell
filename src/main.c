/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:26:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/07 15:16:59 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execution.h"

int main(int argc, char **argv, char **env)
{
	char *str;
	(void)argc;
	(void)argv;

	init_signals();
	init_data(&data, env);
	while (1)
	{
		if (_readline_(&str))
			continue;
		else
		{
			set_data(&data, str);
			expand_env(&data);
			init_shell(&data);
			free(str);
			free(data.input);
			free_tokens_list(data.tokens);
		}
	}
	return (0);
}
