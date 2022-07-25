/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 09:52:39 by enoye             #+#    #+#             */
/*   Updated: 2021/11/19 14:35:01 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static char	*zapolnyaem(char *string, int len, int n)
{
	string = string + len - 1;
	while (n != 0)
	{
		*string = '0' + (n % 10);
		string--;
		n = n / 10;
	}
	if (string[0] != '-')
		string++;
	return (string);
}

static int	getlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*getmemoryxd(char *str, int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	while (n / 10 != 0)
	{	
		size++;
		n = n / 10;
	}
	str = malloc ((size + 1) * 1);
	if (str == 0)
		return (0);
	str[size] = '\0';
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*string;
	char	a;
	int		len;

	string = &a;
	string = getmemoryxd(string, n);
	if (string == 0)
		return (0);
	if (n == 0)
	{	
		*string = '0';
		return (string);
	}
	len = getlen(n);
	if (n == -2147483648)
	{
		string[len - 1] = '8';
		len = len - 1;
		n = n / 10;
	}
	if (n < 0)
		n = -n;
	string = zapolnyaem(string, len, n);
	return (string);
}
