/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:40:58 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/27 14:55:28 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** So a C program can get access to the global environment using
**
** extern char **environ; (man 7 environ)
**
** However, this array is not allocated, so we will grab its contents and
** create our own allocated array. We will reallocate it each time we need
** to add a new environment variable or delete one.
*/

/*
** envsize() counts the number of elements in a null-terminated string array.
*/

int		envsize(char **our_env)
{
	int i;

	if (!our_env)
		return (0);
	i = 0;
	while (our_env[i])
		i++;
	return (i);
}

/*
** add_env() frees the old our_env, and sets it to a new array containing a
** new entry.
*/

void	add_env(char ***our_env, char *entry)
{
	char	**new_env;
	int		i;
	char	*new_entry;

	i = 0;
	if (!(new_env = malloc(sizeof(char *) * (envsize(*our_env) + 2))))
		exit(-1);
	while (*our_env && (*our_env)[i])
	{
		new_env[i] = (*our_env)[i];
		i++;
	}
	new_entry = ft_strdup(entry);
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	if (*our_env)
		free(*our_env);
	*our_env = new_env;
}

/*
** concat_env() takes a "key=value" string, finds key in our_env, and
** concatenates the new value to the old value.
*/

void	concat_env(char ***our_env, char *entry)
{
	int i;
	i = 0;
	while ((*our_env)[i])
	{
		if (!ft_strncmp((*our_env)[i], entry, find_equals((*our_env)[i])))
			break;
		i++;
	}
	(*our_env)[i] = ft_strjoin((*our_env)[i], &entry[find_equals(entry)+1],
										ft_strlen(&entry[find_equals(entry)]));
}

/*
** init_env() grabs the global environment and transforms it into a
** malloc'd null-terminated array of null-terminated strings.
*/

char 	*new_shlvl(char *shlvl)
{
	int i;
	char *new;
	int lvl;
	char *num;

	i = 0;
	new = ft_strdup("SHLVL");
	if (shlvl != NULL)
	{
		while (shlvl[i])
		{
			if (shlvl[i] >= '0' && shlvl[i] <= '9')
			{
				lvl = atoi(&shlvl[i]) + 1;
				num = ft_itoa(lvl);
				num[0] = '=';
				break ;
			}
			i++;
		}
	}
	if (shlvl == NULL || !shlvl[i])
		num = ft_strdup("=1");
	new = ft_strjoin(new, num, ft_strlen(num) + 1);
	free(num);
	return (new);
}
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
		while(our_env[i][j])
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
