/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 15:13:21 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define DEF_FD -1

/*
** is() returns 1 if a token equals query, and 0 otherwise.
*/

int is(char *token, char *query)
{
	return (!ft_strncmp(token, query, ft_strlen(token)));
}

/*
** is_special() returns 1 if a token is a special symbol (;/>/>>/|), and
** 0 otherwise.
*/

int is_special(char *token)
{
	return (is(token, ";") || is(token, ">") || is(token, ">>") 
				|| is(token, "|") || is(token, "<"));
}

/*
** next_special() returns the index of the next token containing a special
** symbol, and -1 if there is no such token in the given array.
*/

int next_special(char **tokens)
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


/*
** drain() writes content to a given fd.
*/

void drain(char *content, int fd)
{
	int len;

	len = ft_strlen(content);
	write(fd, content, len);
}

/*
** cjoin() stitches two strings together, putting delim between them.
*/

char *cjoin(char *a, char *b, char *delim)
{
	char *first;
	char *result;

	first = ft_strjoin(a, delim);
	result = ft_strjoin(first, b);
	free(first);
	return(ft_strjoin(first,b));
}

/*
** execute() returns the result of the evaluation of tokens, passing an fd
** to any function it will launch
*/

char *execute(char **tokens, int fd)
{
	int special;
	int piped[2];

	special = next_special(tokens);

	if (special == -1)
		return(switchboard(tokens, DEF_FD));
	if (is(tokens[special], "|"))
	{
		pipe(piped[2]);
		drain(switchboard(tokens, DEF_FD)), piped[1]);
		return (execute(tokens[special + 1], piped[0]));
	}
	else if (is(tokens[special]), ">")
		return (r_to_file(tokens[special + 1], switchboard(tokens, DEF_FD)));
	else if (is(tokens[special]), ">>")
		return (rr_to_file(tokens[special + 1], switchboard(tokens, DEF_FD)));
	else
	{
		return (cjoin(switchboard(tokens, DEF_FD),
							execute(&tokens[special+1], DEF_FD)), "\n");
	}
}

/*
** s_function is a version of an existing function that returns char * and
** possibly takes a piped fd
*/

/*
** switchboard() selects and executes a function
*/

char *switchboard(char **tokens, int fd)
{
	if (is(tokens[0], "echo"))
		return (s_echo(tokens));
	else if (is(tokens[0], "pwd"))
		return (pwd());
	else if (is(tokens[0], "cd"))
		return (s_cd(tokens));
	else if (is(tokens[0], "exit"))
		return (s_exit(tokens));
	else
		return (s_exec(tokens, fd));
}

void	shell_loop_2()
{
	int k = 0;

	execute(tokens, int fd)
}

	char	**tokens;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ft_putstr("> ");
		tokens = tokenize(fd, &ret);

		if (tokens && tokens[0])
		{
			ft_putstr(execute(tokens, DEF_FD));
			free_split(tokens);	
		}
		
	}