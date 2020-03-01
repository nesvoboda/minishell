/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:46 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 19:07:43 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		double_red(&new[size], i);
	else if (buf[*i] != '\0' && buf[*i] != ' ' && buf[*i] != '>')
		ft_add_delim(&new[size], buf[*i]);
	else
		new[size] = NULL;
	*input = NULL;
	if (*tokens != NULL)
		free(*tokens);
	*tokens = new;
	return (*tokens);
}

char	**ft_newline(char **old, t_info *info)
{
	char	*line;
	char	**tokens;
	int		ret;

	tokens = NULL;
	ret = get_next_line(0, &line);
	if (ret == 0)
	{
		ft_puterr(info->program_name);
		ft_puterr(": syntax error: unexpected end of file\n");
		free(line);
		free_split(old);
		info->status = 258;
		return (NULL);
	}
	tokens = ft_analyser(line, tokens, info);
	if (g_kek == 0)
	{
		free(line);
		return (tokens);
	}
	free(line);
	tokens = tabjoin(old, tokens);
	return (tokens);
}

void	ft_errors_in_tokens(char ***tokens, t_info *info, int q[3])
{
	if (ft_tablen(*tokens) != 1 &&
		is((*tokens)[ft_tablen(tokens[0]) - 1], "|"))
	{
		write(1, " > ", 3);
		if (!(*tokens = ft_newline(*tokens, info)))
		{
			*tokens = malloc(sizeof(char *) * 1);
			(*tokens)[0] = NULL;
		}
	}
	else if (is((*tokens)[0], "|"))
	{
		syntax_error((*tokens)[0], &info->status);
		free((*tokens)[0]);
		(*tokens)[0] = NULL;
	}
	if (q[0] || q[1] || q[2])
	{
		write(2, "NO MULTILINE\n", 13);
		free_split(*tokens);
		*tokens = malloc(sizeof(char *) * 1);
		(*tokens)[0] = NULL;
	}
}

char	**ft_analyser(char *line, char **tokens, t_info *info)
{
	int		i;
	int		q[3];
	char	*input;

	ft_start_input(&input, &i, &tokens, q);
	while (line[i])
	{
		if ((line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i]
			== '<' || line[i] == ' ') && q[0] == 0 && q[1] == 0 && q[2] == 0)
			create_token(&tokens, line, &input, &i);
		if ((line[i] == '\'' || line[i] == '"' || line[i] == '\\') && q[2] == 0)
			set_quotes(&line[i], q, i);
		if (!((line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i]
			== '<' || line[i] == ' ') && q[1] == 0) || q[2] > 0 || q[0] == 1)
			ft_add_char(&input, line[i]);
		if (q[2] != i + 1)
			q[2] = 0;
		i++;
	}
	create_token(&tokens, line, &input, &i);
	ft_errors_in_tokens(&tokens, info, q);
	return (tokens);
}

char	**ft_get_command(t_info *info)
{
	char	*line;
	char	**tokens;
	int		ret;

	tokens = NULL;
	(void)info;
	ret = get_next_line(0, &line);
	if (ret == 0)
	{
		write(1, "exit\n", 5);
		exit(info->status);
	}
	tokens = ft_analyser(line, tokens, info);
	free(line);
	return (tokens);
}
