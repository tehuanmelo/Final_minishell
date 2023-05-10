/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:13:41 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/10 12:13:44 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unset_built_in(t_data *data, char **args)
{
	int	idx;
	int	j;
	int	result;

	result = EXIT_SUCCESS;
	j = 1;
	while (args[j])
	{
		if (!check_for_the_env_key(args[j]) || ft_strchr(args[j], '=') != NULL)
		{
			result = EXIT_FAILURE;
		}
		else
		{
			idx = fetch_env_variable_index(data->env, args[j]);
			if (idx != -1)
				delete_the_env_variables(data, idx);
		}
		j++;
	}
	return (result);
}
