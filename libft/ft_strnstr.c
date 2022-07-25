/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:56:19 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 10:03:27 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	char	*runman;
	size_t	curlen;

	runman = (char *) haystack;
	if (*needle == '\0')
		return (runman);
	while (*runman != '\0' && len != 0)
	{
		if (*runman == *needle)
		{
			i = 0;
			curlen = len;
			while ((runman[i] == needle[i]) && needle[i] != '\0' && curlen != 0)
			{	
				i++;
				curlen--;
			}
			if (needle[i] == '\0')
				return (runman);
		}
		runman++;
		len--;
	}
	return (0);
}
