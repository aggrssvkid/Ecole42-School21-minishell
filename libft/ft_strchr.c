/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:54:35 by enoye             #+#    #+#             */
/*   Updated: 2021/10/17 09:41:05 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*runingman;
	int		x;

	if (c >= 256)
	{
		x = c / 256;
		c = c - (256 * x);
	}
	runingman = (char *) s;
	while (*runingman != c && *runingman != '\0')
		runingman++;
	if (*runingman == '\0' && c == '\0')
		return (runingman);
	if (*runingman == '\0' && c != '\0')
		return (0);
	return (runingman);
}
