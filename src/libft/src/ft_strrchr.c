/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:05 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:42 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The strchr() function locates the first occurrence of c (converted to
//      a char) in the string pointed to by s.  The terminating null charac-
//      ter is considered to be part of the string; therefore if c is `\0',
//      the functions locate the terminating `\0'.

//      The strrchr() function is identical to strchr(), except it locates
//      the last occurrence of c.

// RETURN VALUES
//      The functions strchr() and strrchr() return a pointer to the located
//      character, or NULL if the character does not appear in the string.

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return (&((char *)s)[len]);
		len--;
	}
	return (NULL);
}

// int main()
// {
//     int c = 111;
//     char *str = "hello world";
//     printf("%s\n", ft_strrchr(str, c));
//     return (0);
// }