/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 16:25:03 by ashishae         ###   ########.fr       */
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

/*
** execute() returns the result of the evaluation of tokens, passing an fd
** to any function it will launch
*/

void	execute(char **tokens, int fd, int output)
{
	// int special;
	// int piped[2];

	// special = next_special(tokens);

	// if (special == -1)
	// 	return(switchboard(tokens, DEF_FD));
	// if (is(tokens[special], "|"))
	// {
	// 	pipe(piped[2]);
	// 	//drain(switchboard(tokens, DE>)), piped[1]);
	// 	return (execute(tokens[special + 1], piped[0]));
	// }
	// else if (is(tokens[special]), ">")
	// 	return (r_to_file(tokens[special + 1], switchboard(tokens, DEF_FD)));
	// else if (is(tokens[special]), ">>")
	// 	return (rr_to_file(tokens[special + 1], switchboard(tokens, DEF_FD)));
	// else
	// {
	// 	return (cjoin(switchboard(tokens, DEF_FD),
	// 						execute(&tokens[special+1], DEF_FD)), "\n");
	// }

	(void)fd;
	(void)output;
	return (switchboard(tokens, DEF_FD));
}

/*
** s_function is a version of an existing function that returns char * and
** possibly takes a piped fd
*/

/*
** switchboard() selects and executes a function
*/

void	switchboard(char **tokens, int fd)
{
	if (is(tokens[0], "echo"))
		ft_echo(tokens, 1);
	else if (is(tokens[0], "pwd"))
		print_pwd(1);
	else if (is(tokens[0], "cd"))
		ft_cd(tokens);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens);
	else
		ft_exec(tokens, fd, 1);
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
		execute(com, DEF_FD, 1);

		// Diangostic output
		// while (com[i] != NULL)
		// {
		// 	printf("token%d %s\n",i, com[i]);
		// 	i++;
		// }
		// i = 0;
	}
}