/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:41:15 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 09:37:45 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*runingman;
	int		x;

	if (c >= 256)
	{
		x = c / 256;
		c = c - (x * 256);
	}
	runingman = (char *) s;
	while (n != 0)
	{
		if (*runingman == c)
			return (runingman);
		runingman++;
		n--;
	}
	return (0);
}
