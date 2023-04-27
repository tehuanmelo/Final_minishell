/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 08:27:01 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:05:50 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
**      The strdup() function allocates sufficient memory for a copy of the
**      string s1, does the copy, and returns a pointer to it. The pointer may
**      subsequently be used as an argument to the function free(3).
** 
**      If insufficient memory is available, NULL is returned and errno is set
**      to ENOMEM.
** 
**      The strndup() function copies at most n characters from the string s1
**      always NUL terminating the copied string.
*/

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;

	new = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	return (new);
}
