/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:24:48 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:12:19 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The ft_memchr() function locates the first occurrence of c
//      (converted to an unsigned char) in string s.
// RETURN VALUES
//      The ft_memchr() function returns a pointer to the byte located,
//      or NULL if no such byte exists within n bytes.

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};

// 	printf("%s\n", ft_memchr(s, 2 + 256, 3));
// 	printf("%s\n", memchr(s, 2 + 256, 3));
// 	return (0);
// }