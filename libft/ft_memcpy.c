/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:02:57 by enoye             #+#    #+#             */
/*   Updated: 2021/10/13 18:09:06 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*runingman;
	unsigned char	*wtf;

	if (src == 0 && dst == 0)
		return (dst);
	runingman = (unsigned char *) dst;
	wtf = (unsigned char *) src;
	while (len != 0)
	{
		*runingman = *wtf;
		runingman++;
		wtf++;
		len--;
	}
	return (dst);
}
