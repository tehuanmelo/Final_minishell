/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:24:54 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:13 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters
//      s1: The prefix string.
//      s2: The suffix string.
// Return value
//      The new string.
//      NULL if the allocation fails.
// External functs.
//      malloc
// Description
//      Allocates (with malloc(3)) and returns a new
//      string, which is the result of the concatenation
//      of ’s1’ and ’s2’.

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	length;
	int		i;

	if (!(s1 && s2))
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	new = malloc((length + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = 0;
	return (new);
}

// int main()
// {
//     char *s1 = "hello";
//     char *s2 = "hello";
//     printf("%s\n", ft_strjoin(s1,s2));
// }