/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:28:49 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 16:57:24 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(char *s1, char *s2)
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

void	echo_helper(char **tokens, int fd, int flag)
{
	if ((!(flag)) && !is_special(tokens[0]))
		write(fd, " ", 1);
	if (is_special(tokens[0]))
		return ;
	else
	{
		tokens[0] = ft_copy_without_quotes(tokens[0]);
		write(fd, tokens[0], ft_strlen(tokens[0]));
	}
}

int		ft_echo(char **tokens, int fd)
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
		echo_helper(&tokens[k], fd, flag);
		flag = 0;
		k++;
	}
	if (!flag2)
		write(fd, "\n", 1);
	return (0);
}
