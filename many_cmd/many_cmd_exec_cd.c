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

static void	cd_home_env(char **oldpwd, char **pwd, char **home)
{
	g_status = 0;
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit(1);
	}
	else if (chdir(*home) == FAIL)
	{
		ft_perror(3, "minishell: cd: ", *home, ": ");
		exit(1);
	}
	else
		refresh_wd_paths(oldpwd, pwd);
}

static void	cd_tilda(char **oldpwd, char **pwd, char **home, char *path)
{
	char	*buf;

	g_status = 0;
	if (ft_strcmp(path, "~") == EQUAL)
	{
		if (home == NULL || ft_strcmp(*home, "") != EQUAL)
		{
			if (home == NULL)
				buf = getenv("HOME");
			else
				buf = *home;
			if (chdir(buf) == FAIL)
			{
				ft_perror(3, "minishell: cd: ", buf, ": ");
				exit(1);
			}
			else
				refresh_wd_paths(oldpwd, pwd);
		}
	}
	else
	{
		buf = ft_strjoin("/Users/", path + 1);
		if (chdir(buf) == FAIL)
		{
			ft_perror(3, "minishell: cd: ", buf, ": ");
			exit(1);
		}
		else
			refresh_wd_paths(oldpwd, pwd);
		free(buf);
	}
}

static void	cd_dash(char **oldpwd, char **pwd, char **home, char *opt)
{
	g_status = 1;
	if (ft_strcmp(opt, "-") == EQUAL && oldpwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		exit (1);
	}
	else if (ft_strcmp(opt, "-") == EQUAL)
	{
		if (chdir(*oldpwd) == FAIL)
		{
			ft_perror(3, "minishell: cd: ", *oldpwd, ": ");
			exit (1);
		}
		else
		{
			refresh_wd_paths(oldpwd, pwd);
			ft_putstr_fd(*pwd, 1);
			write(1, "\n", 1);
		}
	}
	else if (ft_strcmp(opt, "--") == EQUAL && home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit(1);
	}
	else if (ft_strcmp(opt, "--") == EQUAL)
	{
		if (chdir(*home) == FAIL)
		{
			ft_perror(3, "minishell: cd: ", *home, ": ");
			exit(1);
		}
		else
		{
			refresh_wd_paths(oldpwd, pwd);
			ft_putstr_fd(*pwd, 1);
			write(1, "\n", 1);
		}
	}
}

static void	cd_path(char **oldpwd, char **pwd, char *path)
{
	if (chdir(path) == FAIL)
	{
		ft_perror(3, "minishell: cd: ", path, ": ");
		exit(1);
	}
	else
		refresh_wd_paths(oldpwd, pwd);
}

void	many_cmd_exec_cd(char **args, t_env *env_list)
{
	char	**oldpwd;
	char	**pwd;
	char	**home;

	get_paths(&oldpwd, &pwd, &home, env_list);
	if (args[1] == NULL || ft_strcmp(args[1], "~-") == EQUAL)
		cd_home_env(oldpwd, pwd, home);
	else if (args[1][0] == '~')
		cd_tilda(oldpwd, pwd, home, args[1]);
	else if (args[1][0] == '-')
		cd_dash(oldpwd, pwd, home, args[1]);
	else
		cd_path(oldpwd, pwd, args[1]);
	exit(0);
}