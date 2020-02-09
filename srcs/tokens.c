/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:57:30 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/09 18:35:32 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	ft_tabcpy(char **dst, char **src)
{
	int i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i] != NULL)
	{
		dst[i] = strdup(src[i]);
		free(src[i]);
		i++;
	}
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
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

void	ft_start_input(char **input, char *prev, char ***tokens, int *q)
{
	*input = NULL;
	*prev = '\0';
	*tokens = NULL;
	q[0] = 0;
	q[1] = 0;
}

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

char	**ft_create_token(char ***tokens, char *buf, char **input)
{
	char	**new;
	int		size;

	size = ft_tablen(*tokens);
	if (!(new = malloc(sizeof(char *) * (size + 3))))
		return (NULL);
	ft_tabcpy(new, *tokens);
	if (*input != NULL)
	{
		new[size] = *input;
		size = size + 1;
	}
	if (*buf != '\n' && *buf != ' ' && *buf != '>' && *buf != '$')
	{
		if (!(ft_add_delim(&new[size], buf[0])))
			return (NULL);
	}
	else
		new[size] = NULL;
	*input = NULL;
	if (*tokens != NULL)
		free(*tokens);
	*tokens = new;
	buf[0] = ' ';
	return (*tokens);
}

void	ft_set_quotes(char buf, int *q)
{
	if (buf == '\'' && q[0] == 1 && (q[1] == 0))
		q[0] = 0;
	else if (buf == '\'' && q[0] == 0 && (q[1] == 0))
			q[0] = 1;
	else if (buf == '\"' && q[1] == 1 && (q[0] == 0))
		q[1] = 0;

	else if (buf == '\"' && q[1] == 0 && q[0] == 0)
		q[1] = 1;
}

char	**ft_get_command(void)
{
	char	buf;
	char	prev;
	char	*input;
	int		q[3];
	char	**tokens;
	ft_start_input(&input, &prev, &tokens, q);
	while ((q[2] = read(0, &buf, 1)))
	{
		if (buf == '\n' && prev != '\\' && q[0] == 0 && q[1] == 0)
			return (ft_create_token(&tokens, &buf, &input));
		if (buf == '\n' && (q[0] == 1 || q[1] == 1 || prev == '\\'))
			write(1, "> ", 2);
		if ((buf == ';' || buf == '<' || buf == '$' || buf == '|' || buf == ' ') && (q[1] ==
				0 && q[0] == 0 && prev != '\\'))
			ft_create_token(&tokens, &buf, &input);
		if ((buf == '\'' || buf == '\"') && prev != '\\')
			ft_set_quotes(buf, q);
		if (!((((buf == ';' || buf == '<' || buf == '|' || buf == ' ') && q[1]
			== 0 && prev != '\\') || buf == '\\' || buf == '\n')) || q[0] == 1)
			ft_add_char(&input, buf);
		if ((prev == '>') && buf == '>')
			ft_create_token(&tokens, &buf, &input);
		prev = buf;
	}
	if (q[2] == 0 || q[2] == -1)
		ft_exit(0);
	return (tokens);
}
