/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:39:47 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 10:24:59 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static void	copy(size_t dstsize, size_t dstlen, char *tmpdst, char *runingman)
{
	while (((dstsize - 1) - dstlen > 0) && *runingman != '\0')
	{
		*tmpdst = *runingman;
		runingman++;
		tmpdst++;
		dstsize--;
	}
	*tmpdst = '\0';
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	char	*runingman;
	char	*tmpdst;
	size_t	dstlen;
	size_t	sum;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	runingman = (char *) src;
	tmpdst = dst + dstlen;
	if (dstsize == 0)
		return (srclen);
	if (dstlen > dstsize)
		sum = srclen + dstsize;
	else
		sum = srclen + dstlen;
	if (dstsize - 1 > dstlen)
		copy(dstsize, dstlen, tmpdst, runingman);
	return (sum);
}
