/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:31:38 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:31 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	if (!s || !f)
		return (0);
	new = ft_calloc(ft_strlen(s) + 1, sizeof(*s));
	if (!new)
		return (0);
	i = 0;
	while (*s)
	{
		new[i] = f(i, *s);
		i++;
		s++;
	}
	return (new);
}

// int main()
// {
//     printf("%s\n", ft_strmapi("something", print));
// }