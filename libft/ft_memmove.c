/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 12:18:17 by enoye             #+#    #+#             */
/*   Updated: 2021/10/13 15:49:11 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*runingman;
	unsigned char	*wtf;

	if (dst == 0 && src == 0)
		return (dst);
	runingman = (unsigned char *) dst;
	wtf = (unsigned char *) src;
	if ((dst > src) && ((src + len) > dst))
	{
		runingman = runingman + len - 1;
		wtf = wtf + len - 1;
		while (len != 0)
		{
			*runingman = *wtf;
			runingman--;
			wtf--;
			len--;
		}
		return (dst);
	}
	dst = ft_memcpy(dst, src, len);
	return (dst);
}
