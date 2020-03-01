/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:05:40 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 19:08:57 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_add_delim(char **new, char delim)
{
	char *del;

	if (!(del = malloc(sizeof(char) * 2)))
		return (NULL);
	del[0] = delim;
	del[1] = '\0';
	new[0] = del;
	new[1] = NULL;
	return (new);
}

void	single_red(char **new)
{
	char *del;

	if (!(del = malloc(sizeof(char) * 2)))
		return ;
	del[0] = '>';
	del[1] = '\0';
	new[0] = del;
	new[1] = NULL;
}

void	double_red(char **new, int *i)
{
	char *del;

	if (!(del = malloc(sizeof(char) * 3)))
		return ;
	del[0] = '>';
	del[1] = '>';
	del[2] = '\0';
	new[0] = del;
	new[1] = NULL;
	*i = *i + 1;
}

void	set_quotes(char *line, int *q, int i)
{
	if (*line == '\\' && q[0] == 0)
		q[2] = i + 1;
	if (*line == '\'' && q[0] == 1 && q[1] == 0)
		q[0] = 0;
	else if (*line == '\'' && q[0] == 0 && (q[1] == 0) && (q[2] == 0))
		q[0] = 1;
	else if (*line == '\"' && q[1] == 1 && (q[0] == 0) && q[2] == 0)
		q[1] = 0;
	else if (*line == '\"' && q[1] == 0 && q[0] == 0 && q[2] == 0)
		q[1] = 1;
}
