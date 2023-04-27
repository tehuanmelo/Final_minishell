/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:59:22 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/01/29 20:18:16 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This version of the atoi function also checks whatever is after the last 
number, if detects any character other than a number returns zero. */

#include "../inc/libft.h"

int	ft_atoi_nbr(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (sign == -1 && res * sign < INT_MIN)
			return (0);
		if (sign == 1 && res > INT_MAX)
			return (0);
		str++;
	}
	if ((*str && *str < '0') || (*str && *str > '9'))
		return (0);
	return (res * sign);
}
