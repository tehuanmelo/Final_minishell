/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:13:31 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/25 19:14:02 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd_built_in(t_data *data, char **args)
{
	char	command[1024];

	(void)data;
	if (ft_strcmp(args[0], "pwd") == 0)
	{
		if (getcwd(command, sizeof(command)) != NULL)
		{
			printf("%s\n", command);
		}
		else
			perror("Error: ");
	}
	return (0);
}
