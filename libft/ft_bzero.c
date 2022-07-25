/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:59:50 by enoye             #+#    #+#             */
/*   Updated: 2021/10/08 16:08:00 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*runingman;

	runingman = s;
	while (n != 0)
	{
		*runingman = '\0';
		n--;
		runingman++;
	}
	return (s);
}
