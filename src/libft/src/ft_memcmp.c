/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:30:32 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:03:32 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The ft_memcmp() function compares byte string s1 against byte string s2.
//      Both strings are assumed to be n bytes long.
// RETURN VALUES
//      The ft_memcmp() function returns zero if the two strings are identical,
//      otherwise returns the difference between the first two differing bytes
//      (treated as unsigned char values, so that `\200' is greater than `\0',
//		for
//      example).  Zero-length strings are always identical.
//      This behavior is not required by C and portable code should only
//      depend on the sign of the returned value.

#include "../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
