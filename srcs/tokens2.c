/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:46 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/21 21:11:31 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tabcpy(char **dst, char **src)
{
	int i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i] != NULL)
	{
		dst[i] = ft_strdup(src[i]);
		free(src[i]);
		i++;
	}
	dst[i] = NULL;
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

void 	double_red(char **new)
{
	char *del;

	if (!(del = malloc(sizeof(char) * 3)))
		return ;
	del[0] = '>';
	del[1] = '>';
	del[2] = '\0';
	new[0] = del;
	new[1] = NULL;
}
void 	set_quotes(char *line, int *q)
{
	if (*line == '\\' && q[0] == 0)
		q[2] = 1;
	if (*line == '\'' && q[0] == 1 && q[1] == 0)
		q[0] = 0;
	else if (*line == '\'' && q[0] == 0 && (q[1] == 0) && (q[2] == 0))
		q[0] = 1;
	else if (*line == '\"' && q[1] == 1 && (q[0] == 0) && q[2] == 0)
		q[1] = 0;
	else if (*line == '\"' && q[1] == 0 && q[0] == 0 && q[2] == 0)
		q[1] = 1;
}
char	**create_token(char ***tokens, char *buf, char **input, int *i)
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
	if (buf[*i] == '>' && buf[*i + 1] != '>')
		single_red(&new[size]);
	else if (buf[*i] == '>' && buf[*i + 1] == '>')
	{
		double_red(&new[size]);
		*i = *i + 1;
	}
	else if (buf[*i] != '\0' && buf[*i] != ' ' && buf[*i] != '>')
	{
		if (!(ft_add_delim(&new[size], buf[*i])))
			return (NULL);
	}
	else
		new[size] = NULL;
	*input = NULL;
	if (*tokens != NULL)
		free(*tokens);
	*tokens = new;
	return (*tokens);
}

void	ft_start_input(char **input, int *i, char ***tokens, int *q)
{
	*input = NULL;
	*i = 0;
	*tokens = NULL;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
}

char 	**ft_analyser(char *line, char **tokens)
{
	int i;
	int q[3];
	char *input;

	ft_start_input(&input, &i, &tokens, q);
	while (line[i])
	{
		if ((line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<' || line[i] == ' ') && q[0] == 0 && q[1] == 0 && q[2] == 0)
			create_token(&tokens, line, &input, &i);
		if ((line[i] == '\'' || line[i] == '"' || line[i] == '\\') && q[2] == 0)
			set_quotes(&line[i], q);
		if (!((line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<' || line[i] == ' ') && q[1] == 0) || q[2] == 1 || q[0] == 1)
			ft_add_char(&input, line[i]);
		if (i > 0 && line[i - 1] == '\\' && q[2] == 1)
			q[2] = 0;
		i++;
	}
	create_token(&tokens, line, &input, &i);
	if (q[0] || q[1] || q[2])
	{
		write(2, "NO MULTILINE\n", 13);
		free_split(tokens);
		tokens = malloc(sizeof(char *) * 1);
		tokens[0] = NULL;
	}
	return (tokens);
}

char	**ft_get_command(t_info *info)
{
	char *line;
	char **tokens = NULL;
	int ret;

	ret = get_next_line(0, &line);
	if (ret == 0)
	{
		write(1, "exit\n", 5);
		exit(info->status);
	}
	tokens = ft_analyser(line, tokens);
	free(line);
	return (tokens);
}