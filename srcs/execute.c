/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 19:57:39 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define DEF_FD -1
#include <stdio.h>
#include <string.h>

/*
** execute() returns the result of the evaluation of tokens, passing an fd
** to any function it will launch
*/

void	execute(char **tokens, int fd, int output)
{
	int special;
	int piped[2];
	int new_output;

	special = next_special(tokens);
	if (special == -1)
		switchboard(tokens, fd, output);
	else if (is(tokens[special], "|"))
	{
		pipe(piped);
		switchboard(tokens, fd, piped[1]);
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