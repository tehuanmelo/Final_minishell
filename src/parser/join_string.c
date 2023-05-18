/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aball <aball@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:08:49 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/05/18 21:04:29 by aball            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_string(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

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
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	free(s1);
	return (new);
}
