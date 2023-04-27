/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:27:48 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:40 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The strnstr() function locates the first occurrence of the
// 		null-terminated string needle in the string haystack, where not more
// 		than len characters are searched.
// 		Characters that appear after a `\0' character are not searched.
// 		Since the strnstr() function is a FreeBSD spe-cific API, it should
// 		only be used when portability is not a concern.
// RETURN VALUES
//      If needle is an empty string, haystack is returned; if needle occurs
// 		nowhere in haystack, NULL is returned; otherwise a pointer to the
//      first character of the first occurrence of needle is returned.

#include "../inc/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	match;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len)
	{
		i = 0;
		match = 0;
		if (*haystack == *needle)
		{
			while (needle[i] && i < len)
			{
				if (needle[i] == haystack[i])
					match++;
				i++;
			}
			if (match == ft_strlen(needle))
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
