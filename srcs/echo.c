/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:28:49 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/20 20:35:08 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_echo(char **tokens, int fd)
{
	int k;
	int flag;

	k = 1;
	flag = 0;
	if (tokens[k] != NULL && !ft_strcmp(tokens[k], "-n"))
	{
		k = 2;
		flag = 1;
	}
	while (tokens[k] != NULL && !is_spec(tokens[k]))
	{
		if (((k > 1 && flag == 0) || (k > 2 && flag == 1)) && !is_special(tokens[k]))
			write(fd, " ", 1);
		if (is_special(tokens[k]))
			k++;
		else
		{
			tokens[k] = ft_copy_without_quotes(tokens[k]);
			write(fd, tokens[k], ft_strlen(tokens[k]));
		}
		k++;
	}
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
