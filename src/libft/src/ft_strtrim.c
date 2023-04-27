/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:11:37 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:44 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//     s1: The string to be trimmed.
//     set: The reference set of characters to trim.
// Return value
//     The trimmed string.
//     NULL if the allocation fails.
//     External functs. malloc
// Description
//     Allocates (with malloc(3)) and returns a copy of
//     ’s1’ with the characters specified in ’set’ removed
//     from the beginning and the end of the string.

#include "../inc/libft.h"

int	ft_checkstr(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (ft_checkstr(*s1, set))
			s1++;
		else
			break ;
	}
	i = ft_strlen(s1);
	while (i)
	{
		if (ft_checkstr(s1[i - 1], set))
			i--;
		else
			break ;
	}
	return (ft_substr(s1, 0, i));
}
