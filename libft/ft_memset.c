/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:29:38 by enoye             #+#    #+#             */
/*   Updated: 2021/10/13 15:50:00 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*runingman;

	runingman = (unsigned char *) b;
	while (len != 0)
	{
		*runingman = c;
		len--;
		runingman++;
	}
	return (b);
}
