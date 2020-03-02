/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:02:54 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 23:20:27 by ashishae         ###   ########.fr       */
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
			result[j++] = ft_strdup(tokens[i]);
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
