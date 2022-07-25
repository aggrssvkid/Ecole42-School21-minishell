/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:00:48 by enoye             #+#    #+#             */
/*   Updated: 2021/10/18 13:16:34 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*runingman;
	int		x;

	if (*s == '\0' && c != '\0')
		return (0);
	runingman = (char *) s + ft_strlen(s);
	if (c == '\0')
		return (runingman);
	else
		runingman--;
	if (c >= 256)
	{
		x = c / 256;
		c = c - (256 * x);
	}
	while (*runingman != c && runingman != s)
		runingman--;
	if (runingman == s && *runingman != c)
		return (0);
	return (runingman);
}
