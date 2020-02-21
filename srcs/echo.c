/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:28:49 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/21 20:25:48 by ablanar          ###   ########.fr       */
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
	int flag2;

	k = 1;
	flag = 1;
	flag2 = 0;
	while (tokens[k] != NULL && !ft_strcmp(tokens[k], "-n"))
	{
		k++;
		flag2 = 1;
	}
	while (tokens[k] != NULL && !is_spec(tokens[k]))
	{
		if ((!(flag)) && !is_special(tokens[k]))
			write(fd, " ", 1);
		if (is_special(tokens[k]))
			k++;
		else
		{
			tokens[k] = ft_copy_without_quotes(tokens[k]);
			write(fd, tokens[k], ft_strlen(tokens[k]));
		}
		flag = 0;
		k++;
	}
	if (!flag2)
		write(fd, "\n", 1);
	return (0);
}
