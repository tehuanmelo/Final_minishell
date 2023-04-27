/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 02:38:58 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:02:03 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Description:
**     Count the number of digits in an integer.
** Return:
**     Returns the number of digits including '-' sign if negative number.
*/

int	ft_intlen(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		counter++;
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}
