/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:26:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/04 18:21:26 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	(void)argc;
	(void)argv;
	(void)env;

	init_signals();
	// init_data(&data, env);
	while (1)
	{
		if (_readline_(&str))
			continue ;
		else
		{
			set_data(&data, str);
			print_tokens(data.tokens);
			expand_env(&data);
			print_tokens(data.tokens);
			init_shell(&data);
			print_comands();
			// data.exit_code = execute(&data);
			// free(str);
			// free(data.input);
			// free_tokens_list(data.tokens);
		}
	}
	return (0);
}
