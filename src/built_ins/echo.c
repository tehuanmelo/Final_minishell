/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:58 by mbin-nas          #+#    #+#             */
/*   Updated: 2023/05/23 20:43:41 by mbin-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_echo_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i] != NULL)
	{	
		if (ft_strcmp(args[i], "\">\"") == 0 || ft_strcmp(args[i], "\'>\'") == 0)
			ft_putchar_fd('>', STDOUT_FILENO);
		else if (ft_strcmp(args[i], "\"<\"") == 0 || ft_strcmp(args[i], "\'<\'") == 0)
			ft_putchar_fd('<', STDOUT_FILENO);
		else if (ft_strcmp(args[i], "\">>\"") == 0 \
		|| ft_strcmp(args[i], "\'>>\'") == 0)
			ft_putstr_fd(">>", STDOUT_FILENO);
		else if (ft_strcmp(args[i], "\"<<\"") == 0 \
		|| ft_strcmp(args[i], "\'<<\'") == 0)
			ft_putstr_fd("<<", STDOUT_FILENO);
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

bool	check_for_n(char *arg)
{
	int		i;
	bool	flag_for_n;

	flag_for_n = false;
	i = 0;
	if (arg[i] != '-')
		return (flag_for_n);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		flag_for_n = true;
	return (flag_for_n);
}

/* ft_echo_built_in:
#	@brief: 
* prints the given strings and adds a \n character or not depending on the 
*  -n option.
# 	@return:
*	Returns 1 on completion.
*/
int	ft_echo_built_in(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && check_for_n(args[i]))
	{
		n_flag = true;
		i++;
	}
	print_echo_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
