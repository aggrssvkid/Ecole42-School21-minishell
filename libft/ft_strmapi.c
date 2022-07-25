/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:12:20 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 10:02:41 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*arr;
	unsigned int	i;

	if (s == 0)
		return (0);
	arr = malloc ((ft_strlen(s) + 1) * 1);
	if (arr == 0)
		return (0);
	arr[ft_strlen(s)] = '\0';
	i = 0;
	while (s[i] != '\0')
	{
		arr[i] = (*f)(i, s[i]);
		i++;
	}
	return (arr);
}
