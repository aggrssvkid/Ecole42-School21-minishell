/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoye <enoye@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:20:44 by enoye             #+#    #+#             */
/*   Updated: 2022/04/24 14:20:52 by enoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"

static int	if_file_exist(char *name, int n)
{
	int	x;

	x = open(name, O_DIRECTORY);
	if (x != -1)
	{
		close(x);
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": THIS IS PAPKA!\n", 2);
		if (n != 1)
			exit(1);
		else
			return (0);
	}
	if (access(name, W_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": Ne mogu suda zapisat info >:(\n", 2);
		if (n != 1)
			exit(1);
		else
			return (0);
	}
	return (1);
}

int	check_in_out_file(char *name, int *fd_in, int n)
{
	int	fd;

	if (access(name, F_OK) == -1)
	{
		if (*name == '\0')
		{
			ft_putstr_fd("mshell: ne mogu sozdat file bez imeni\n", 2);
			return (0);
		}
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = open(name, O_RDWR + O_CREAT, 0644);
		return (1);
	}
	else
	{
		fd = open(name, O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			ft_putstr_fd("mshell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ZDAROVA OTEC! ETO PAPOCHKA!\n", 2);
			if (n != 1)
				exit(1);
			else
				return (0);
		}
		if (access(name, R_OK) == -1)
		{
			ft_putstr_fd("mshell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": Can't poluchit dostup k file!", 2);
			ft_putstr_fd("Sorry, good buy Amerika!\n", 2);
			if (n != 1)
				exit(1);
			return (0);
		}
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = open(name, O_RDWR, 0644);
	}
	return (1);
}

int	check_input_file(char *name, int *fd_in, int n)
{
	if (access(name, F_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": Net file or director.Poiwi v drugom meste,clown\n", 2);
		if (n != 1)
			exit(1);
		return (0);
	}
	if (access(name, R_OK) == -1)
	{
		ft_putstr_fd("mshell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": Nu ti i clown, ya ne mogu prochitat etot file!!\n", 2);
		if (n != 1)
			exit(1);
		return (0);
	}
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = open(name, O_RDWR, 0644);
	return (1);
}

int	check_output_file(char *name, int nbr_rdrct, int n)
{
	int	fd;

	fd = 1;
	if (access(name, F_OK) == -1)
	{
		if (*name == '\0')
		{
			ft_putstr_fd("mshell: ne mogu sozdat file bez imeni\n", 2);
			return (0);
		}
		fd = open(name, O_CREAT + O_RDWR, 0644);
		return (fd);
	}
	else
	{
		if (if_file_exist(name, n) == 0)
			return (0);
	}
	if (nbr_rdrct == 1)
		fd = open(name, O_TRUNC + O_RDWR, 0644);
	else if (nbr_rdrct == 2)
		fd = open(name, O_APPEND + O_RDWR, 0644);
	return (fd);
}
