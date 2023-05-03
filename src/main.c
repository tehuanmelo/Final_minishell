/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:26:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/04/28 15:47:36 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	(void)argc;
	(void)argv;

	init_signals();
	init_data(&data, env);
	while (1)
	{
		if (_readline_(&str))
		{
			continue ;
		}
		else
		{
			set_data(&data, str);
			expand_env(&data);
			init_shell(&data);
			// print_t_data(&data);
			// printf("Executing command...\n");
			data.exit_code = execute(&data);
			printf("Hello !\n");
			free(str);
			free(data.input);
			free_tokens_list(data.tokens);
		}
	}
	// printf("Return value %d\n", _readline_(&str));
	return (0);
}
