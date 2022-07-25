/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:27:14 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 11:07:58 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		lenstr;

	if (s == 0)
		return (0);
	lenstr = ft_strlen(s);
	if (start >= lenstr)
	{
		substr = malloc(1 * 1);
		if (substr == 0)
			return (0);
		*substr = '\0';
		return (substr);
	}
	if (len > (lenstr - start))
		len = lenstr - start;
	substr = malloc((len + 1) * sizeof (char));
	if (substr == 0)
		return (0);
	len = ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
