/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:26:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/04/27 14:12:33 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include "../inc/execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	// t_data	data;
	(void)argc;
	(void)argv;

	init_signals();
	init_data(&data, env);
	while (1)
	{
		
		print_t_data(&data);
		// printf(COLOR_RED "I am string %s\n", str);
		if (_readline_(&str))
		{
			continue ;
		}
		else
		{
			set_data(&data, str);
			expand_env(&data);
			init_shell(&data);
			print_t_data(&data);
			// printf("Executing command...\n");
			int execute_result = execute(&data);
			if (execute_result != 0) {
				// Handle the result of the execute function if necessary
				return (0);
			}
			free(str);
			free(data.input);
			free_tokens_list(data.tokens);
		}
	}
	// printf("Return value %d\n", _readline_(&str));
	return (0);
}
