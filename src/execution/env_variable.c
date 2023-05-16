/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:09:48 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/16 14:11:33 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* check_for_the_env_key
* @brief: Checks for the env string in the enviornment
* @return: Returns true if the variable are valid 
* @example: "HOME" && "PATH" are valid therefore returns true. 
*/
bool	check_for_the_env_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/* count_env_variables
* @brief: Counts the original enviornment variables 
* @returns: the total number of enviornment variables
*/
int	count_env_variables(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/* fetch_env_variable_value
* @brief: Fetches the env variable characters of the command in the enviornment
* @return: Returns an char of the command in the enviornment
*/
char	*fetch_env_variable_char(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
		{
			free(temp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free(temp);
	return (NULL);
}

/* fetch_env_variable_index
* @brief: Fetcjes the env variable position of the command in the enviornment
* @return: Returns an index of the position of the command in the enviornment
*/
int	fetch_env_variable_index(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
		{
			free(temp);
			return (i);
		}
		i++;
	}
	free(temp);
	return (-1);
}
