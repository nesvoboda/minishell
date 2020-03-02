/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:07:02 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 22:07:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_start_input(char **input, int *i, char ***tokens, int *q)
{
	*input = NULL;
	*i = 0;
	*tokens = NULL;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
}

int		next_semi(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is(tokens[i], ";"))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_add_char(char **line, char c)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char) * ft_strlen(*line) + 2)))
	{
		free(*line);
		return (NULL);
	}
	i = 0;
	if (*line != NULL)
	{
		while ((*line)[i])
		{
			new[i] = (*line)[i];
			i++;
		}
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (line != NULL)
		free(*line);
	*line = new;
	return (*line);
}

int		ft_strlen(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i])
		i++;
	return (i);
}
