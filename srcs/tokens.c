/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:57:30 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/07 20:46:47 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	q[1] = 1;
}

char	**ft_create_token(char ***tokens, char *buf, char **input)
{
	char	**new;
	int		size;
	char	*delim;

	size = ft_tablen(*tokens);
	new = malloc(sizeof(char *) * (size + 3));
	ft_tabcpy(new, *tokens);
	if (*input != NULL)
	{
		new[size] = *input;
		if (*buf != '\n' && *buf != ' ' && *buf != '>')
		{
			delim = malloc(sizeof(char) * 2);
			delim[0] = buf[0];
			delim[1] = '\0';
			new[size + 1] = delim;
			new[size + 2] = NULL;
		}
		else
			new[size + 1] = NULL;
	}
	else
	{
		if (*buf != '\n' && *buf != ' ' && *buf != '>')
		{
			delim = malloc(sizeof(char) * 2);
			delim[0] = buf[0];
			delim[1] = '\0';
			new[size] = delim;
			new[size + 1] = NULL;
		}
		else
			new[size] = NULL;
	}
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
	if (buf == '\"' && q[1] == 1 && (q[0] == 0))
		q[1] = 0;
	if (buf == '\'' && q[0] == 0 && (q[1] == 0))
		q[0] = 1;
	if (buf == '\"' && q[1] == 0 && q[0] == 0)
		q[1] = 0;
}

char	**ft_get_command(void)
{
	char	buf;
	char	prev;
	char	*input;
	int		q[2];
	char	**tokens;

	ft_start_input(&input, &prev, &tokens, q);
	while (read(0, &buf, 1))
	{
		if (buf == '\n' && prev != '\\' && q[0] == 0 && q[1] == 0)
			return (ft_create_token(&tokens, &buf, &input));
		if (buf == '\n' && (q[0] == 1 || q[1] == 1 || prev == '\\'))
			write(1, "> ", 2);
		if ((buf == ';' || buf == '<' || buf == '|' || buf == ' ') && (q[1] ==
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
	return (tokens);
}
