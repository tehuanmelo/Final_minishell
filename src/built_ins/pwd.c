/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:13:31 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/10 12:13:32 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd_built_in(t_data *data, char **args)
{
	char	command[1024];

	(void)data;
	if (strcmp(args[0], "pwd") == 0)
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
