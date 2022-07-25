/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:11:06 by enoye             #+#    #+#             */
/*   Updated: 2021/11/08 22:29:19 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

typedef struct s_var
{
	char	buffer[BUFFER_SIZE + 1];
	char	*runman;
	char	*tmp;
	char	*fre;
	char	*getline;
	int		n;

}	t_var;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
