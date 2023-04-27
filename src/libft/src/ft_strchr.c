/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:01:01 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:05:46 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The strchr() function locates the first occurrence of c
//      (converted to a char) in the string pointed to by s.
//      The terminating null charac-ter is considered to be part of the
//      string; therefore if c is `\0',
//      the functions locate the terminating `\0'.

// RETURN VALUES
//      The functions strchr() and strrchr() return a pointer to the located
//      character, or NULL if the character does not appear in the string.

#include "../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}

// int main()
// {
//     int c = 111;
//     char *str = "hello world";
//     printf("%s\n", ft_strchr(str, c));
//     return (0);
// }