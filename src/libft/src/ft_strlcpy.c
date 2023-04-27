/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:07:55 by tde-melo          #+#    #+#             */
/*   Updated: 2023/01/29 20:06:21 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIPTION
//      The ft_strlcpy() function copy strings with the same input parameters
//      and output result as snprintf(3).  It is designed to be safer,
//      more consistent, and less error prone replacement for the easily
//      misused function strncpy(3).
//      ft_strlcpy() take the full size of the destination buffer and guarantee
//      NUL-termina-tion if there is room.  Note that room for the NUL should
//      be included in dstsize.
//      ft_strlcpy() copies up to dstsize - 1 characters from the string
//      src to dst, NUL-terminating the result if dstsize is not 0.
// RETURN VALUES
//      Besides quibbles over the return type (size_t versus int) and
//      signal handler safety (snprintf(3) is not entirely safe on some
//      systems), the following two are equivalent:
//            n = ft_strlcpy(dst, src, len);
//            n = snprintf(dst, len, "%s", src);
//      Like snprintf(3), the ft_strlcpy() return the total length of the string
//      it tried to create.  That means the length of src.
//      If the return value is >= dstsize, the output string has been
//      truncated.
//      It is the caller's responsibility to handle this.

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	i = 0;
	while (*src && i < dstsize - 1)
		dst[i++] = *src++;
	dst[i] = 0;
	return (srclen);
}
