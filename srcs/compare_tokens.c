/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:58:11 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/18 19:57:02 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** is() returns 1 if a token equals query, and 0 otherwise.
*/

int	is(char *token, char *query)
{
	return (!ft_strncmp(token, query, ft_strlen(token) + 1));
}

/*
** is_special() returns 1 if a token is a special symbol (;/>/>>/|), and
** 0 otherwise.
*/

int	is_special(char *token)
{
	return (is(token, ";") || is(token, ">") || is(token, ">>")
				|| is(token, "|") || is(token, "<"));
}

int	is_spec(char *token)
{
	return (is(token, ";") || is(token, "|"));
}

/*
** next_special() returns the index of the next token containing a special
** symbol, and -1 if there is no such token in the given array.
*/

int next_spec(char **tokens)
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

int	next_special(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is_special(tokens[i]))
			return (i);
		i++;
	}
	return (-1);
}
