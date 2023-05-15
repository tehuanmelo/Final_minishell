/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:08:49 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/07 15:29:01 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_string(char *s1, char *s2)
{
	char	*new;
	int		i;

	if (!s1)
		s1 = ft_calloc(sizeof(char), 1);
	new = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (*s2)
		new[i++] = *s2++;
	new[i] = 0;
	free(s1);
	return (new);
}
