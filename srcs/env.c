/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:40:58 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/04 19:11:40 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!(new_entry = malloc(sizeof(char) * (ft_strlen(entry) + 1))))
		exit(-1);
	ft_strlcpy(new_entry, entry, ft_strlen(entry) + 1);
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	if (*our_env)
		free(*our_env);
	*our_env = new_env;
}

/*
** init_env() grabs the global environment and transforms it into a
** malloc'd null-terminated array of null-terminated strings.
*/

void	init_env(char ***our_env, char **environ)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!(new_env = malloc(sizeof(char *) * (envsize(environ) + 1))))
		exit(-1);
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = NULL;
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
		if (!ft_strncmp(our_env[i], key, ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
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
	if (find_env(*our_env, key))
		new_env_size = envsize(*our_env);
	else
		new_env_size = envsize(*our_env) + 1;
	if (!(new_env = malloc(sizeof(char *) * new_env_size)))
		exit(-1);
	while ((*our_env)[i])
	{
		if (ft_strncmp((*our_env)[i], key, ft_strlen(key)))
			new_env[y++] = (*our_env)[i++];
		else
			i++;
	}
	if (new_env[y - 1] != NULL)
		new_env[y] = NULL;
	free(*our_env);
	*our_env = new_env;
}
