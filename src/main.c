/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:26:41 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/11 16:43:42 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"
#include "../inc/minishell.h"

void	free_env(char **env)
{
	int	i;

	if (env == NULL)
		return ;
	for (i = 0; env[i] != NULL; i++)
	{
		free(env[i]);
	}
	free(env);
}

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
			continue ;
		else
		{
			set_data(&data, str);
			expand_env(&data);
			init_shell(&data);
			free_tokens_list(data.tokens);
		}
	}
	return (0);
}
