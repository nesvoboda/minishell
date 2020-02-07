/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 19:28:29 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define DEF_FD -1
#include <stdio.h>
#include <string.h>

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_size = strlen(s1) + strlen(s2) + 1;
	if ((result = malloc(sizeof(char) * total_size)) == NULL)
		return (NULL);
	memcpy(result, s1, strlen(s1));
	memcpy((result + strlen(s1)), s2, strlen(s2));
	result[total_size - 1] = '\0';
	return (result);
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

void print_pwd(int fd)
{
	int len;
	char *str;

	str = pwd();
	len = ft_strlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
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


int	redir(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	return (fd);
}

int	rredir(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	return (fd);
}

/*
** execute() returns the result of the evaluation of tokens, passing an fd
** to any function it will launch
*/

void	execute(char **tokens, int fd, int output)
{
	int special;
	int piped[2];
	int new_output;

	printf("execute()\n");
	// for (int i = 0; tokens[i]; i++)
	// {
	// 	printf("Token n. %d is %s\n", i, tokens[i]);
	// }
	special = next_special(tokens);
	if (special == -1)
		switchboard(tokens, fd, output);
	else if (is(tokens[special], "|"))
	{
		pipe(piped);
		//drain(switchboard(tokens, DE>)), piped[1]);
		//return (execute(tokens[special + 1], piped[0]));
		switchboard(tokens, fd, piped[1]);
		//write(piped[1], "", 1);
		close(piped[1]);
		execute(&tokens[special + 1], piped[0], output);
		close(piped[0]);

	}
	else if (is(tokens[special], ">"))
	{
		new_output = redir(tokens[special + 1]);
		switchboard(tokens, fd, new_output);
		close(new_output);
	}
	else if (is(tokens[special], ">>"))
	{
		new_output = rredir(tokens[special + 1]);
		switchboard(tokens, fd, new_output);
		close(new_output);
	}
	else
	{
		switchboard(tokens, fd, output);
		switchboard(&tokens[special + 1], fd, output);
	}
}

/*
** s_function is a version of an existing function that returns char * and
** possibly takes a piped fd
*/

/*
** switchboard() selects and executes a function
*/

void	switchboard(char **tokens, int fd, int output)
{
	printf("switchboard()\n");
	(void) output;
	if (is(tokens[0], "echo"))
		ft_echo(tokens, output);
	else if (is(tokens[0], "pwd"))
		print_pwd(1);
	else if (is(tokens[0], "cd"))
		ft_cd(tokens);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens);
	else
		ft_exec(tokens, fd, output);
}

void	shell_loop_2()
{
	char **com;
	int i;

	i = 0;
	while (1)
	{


		write(1, "> ", 2);
		com = ft_get_command();
		// Diangostic output
		// while (com[i] != NULL)
		// {
		// 	printf("token%d %s\n",i, com[i]);
		// 	i++;
		// }
		// i = 0;
		if (com[0] != NULL)
			execute(com, DEF_FD, 1);


	}
}