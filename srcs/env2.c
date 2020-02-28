/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:44:35 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 17:46:02 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_shlvl(char **envs)
{
	int i;

	i = 0;
	while (envs[i])
	{
		if (!ft_strncmp(envs[i], "SHLVL", 5))
			return (1);
		i++;
	}
	return (0);
}

void	init_env(char ***our_env, char **environ)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!(new_env = malloc(sizeof(char *) * (envsize(environ) + 1))))
		exit(-1);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "SHLVL", 5))
			new_env[i] = new_shlvl(environ[i]);
		else
			new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i] = NULL;
	if (!check_shlvl(new_env))
	{
		new_env[i] = new_shlvl(NULL);
		new_env[i + 1] = NULL;
	}
	*our_env = new_env;
}

/*
** find_env() finds an entry in an environment array by its key
*/

int		find_env(char **our_env, char *key)
{
	int i;

	i = 0;
	while (our_env[i])
	{
		if (!ft_strncmp(our_env[i], key, find_equals(key)))
			return (i);
		i++;
	}
	return (-1);
}

void	env_noarg(char **our_env, int output)
{
	int	i;
	int	j;

	i = 0;
	while (our_env[i])
	{
		ft_putstr_fd("declare -x ", output);
		j = 0;
		while (our_env[i][j] != '=')
			write(output, &our_env[i][j++], 1);
		j++;
		write(output, "=\"", 2);
		while (our_env[i][j])
			write(output, &our_env[i][j++], 1);
		write(output, "\"\n", 2);
		i++;
	}
}

/*
** remove_env() removes an entry from an environment array by its key
*/

void	remove_env(char ***our_env, char *key)
{
	char	**new_env;
	int		i;
	int		y;
	int		new_env_size;

	i = 0;
	y = 0;
	if (find_env(*our_env, key) > 0)
		new_env_size = envsize(*our_env);
	else
		new_env_size = envsize(*our_env) + 1;
	if (!(new_env = malloc(sizeof(char *) * new_env_size)))
		exit(-1);
	while ((*our_env)[i])
	{
		if (ft_strncmp((*our_env)[i], key, find_equals(key)))
			new_env[y++] = (*our_env)[i++];
		else
			free((*our_env)[i++]);
	}
	new_env[y] = NULL;
	free(*our_env);
	*our_env = new_env;
}
