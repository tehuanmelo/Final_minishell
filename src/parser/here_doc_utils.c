/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:16:07 by tde-melo          #+#    #+#             */
/*   Updated: 2023/05/24 18:04:49 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_here_doc(char **args)
{
	while (*args)
	{
		if (!ft_strcmp(*args, "<<"))
			return (0);
		args++;
	}
	g_data.heredoc_call = true;
	return (1);
}

char	**get_delimiter(char **input, int nbr_heredocs)
{
	char	**delimiter;
	int		i;

	delimiter = ft_calloc(nbr_heredocs + 1, sizeof(char *));
	i = 0;
	while (*input)
	{
		if (!ft_strcmp("<<", *input))
		{
			delimiter[i++] = ft_strdup(*(++input));
		}
		input++;
	}
	return (delimiter);
}

void	checking_delimiter_index(int *nbr_heredocs, int *i, char **delimiter,
		char *line)
{
	if (ft_strcmp(line, delimiter[*i]) == 0)
	{
		(*nbr_heredocs)--;
		(*i)++;
	}
}

void	free_delimiter(char **delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
		free(delimiter[i++]);
	free(delimiter);
}

int	get_heredoc_nbr(char **args)
{
	int	i;
	int	nbr_heredocs;

	i = 0;
	nbr_heredocs = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			nbr_heredocs++;
		i++;
	}
	return (nbr_heredocs);
}
