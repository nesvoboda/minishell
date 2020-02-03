/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/03 14:50:11 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Remove before flight
#include <stdio.h>

/*
** free_split() free()s an array of strings
*/

void	free_split(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

/*
** tokenize() reads a line from a given fd and splits it into tokens.
*/

char	**tokenize(int fd, int *ret)
{
	char	*line;
	char	**tokens;

	*ret = get_next_line(fd, &line);
	tokens = ft_split(line, ' ');
	free(line);
	return (tokens);
}

void	shell_loop(void)
{
	char	**tokens;
	int		ret;
	
	ret = 1;
	while (ret > 0)
	{
		ft_putstr("> ");
		tokens = tokenize(0, &ret);
		// Diagnostic output
		for (int i = 0; tokens[i] != 0; i++)
		{
			printf("Token #%d is |%s|\n", i, tokens[i]);
		}
		free_split(tokens);
	}
}