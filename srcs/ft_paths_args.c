/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:02:54 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/26 14:14:21 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		next_com(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is_spec(tokens[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	**get_arguments(char **tokens)
{
	char	**result;
	int		length;
	int		i;
	int		j;
	length = next_com(tokens);
	if (length == -1)
		length = ft_tablen(tokens);
	if (!(result = malloc(sizeof(char *) * (length + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (is_special(tokens[i]))
			i++;
		else
		{
			tokens[i] = ft_copy_without_quotes(tokens[i]);
			result[j++] = tokens[i];
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

int		ft_find_paths(char **our_env)
{
	int i;

	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_choose_path(char *paths, char *token)
{
	int		k;
	int		j;
	char	*str;

	j = 0;
	k = 0;
	if (!(str = malloc(sizeof(char) * ft_strlen(paths) +
		ft_strlen(token) + 2)))
		return (NULL);
	while (paths[j] != '\0')
	{
		str[j] = paths[j];
		j++;
	}
	str[j] = '/';
	while (token[k])
	{
		str[j + 1 + k] = token[k];
		k++;
	}
	str[k + j + 1] = '\0';
	return (str);
}

char	*ft_exec_path(char **token, char **our_env)
{
	char			**paths;
	int				num_path;
	struct stat		stats;
	int				i;
	char			*str;

	i = 0;
	num_path = ft_find_paths(our_env);
	if (num_path == -1)
		return (NULL);
	if (!(paths = ft_split(&our_env[num_path][5], ':')))
		return (NULL);
	while (paths[i])
	{
		str = ft_choose_path(paths[i], token[0]);
		if (stat(str, &stats) == 0)
			return (str);
		free(str);
		i++;
	}
	if (stat(token[0], &stats) == 0)
		return (token[0]);
	return (NULL);
}
