/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:47:48 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:02:41 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parameters
**     n: the integer to convert.
** Return value
**     The string representing the integer.
**     NULL if the allocation fails.
** External functs.
**     malloc
** Description
**     Allocates (with malloc(3)) and returns a string
**     representing the integer received as an argument.
**     Negative numbers must be handled.
*/

#include "../inc/libft.h"

char	*ft_itoa(int n)
{
	char		*new;
	int			arrlen;
	long int	nbr;

	nbr = n;
	arrlen = ft_intlen(n);
	new = ft_calloc((arrlen + 1), sizeof(char));
	if (!new)
		return (NULL);
	if (nbr < 0)
		nbr *= -1;
	while (arrlen--)
	{
		new[arrlen] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (n < 0)
		*new = '-';
	return (new);
}
