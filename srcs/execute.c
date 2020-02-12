/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/12 15:37:55 by ashishae         ###   ########.fr       */
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

void	execute(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int piped[2];
	int new_output;
	int	temp;

	special = next_special(tokens);
	if (special == -1)
		switchboard(tokens, fd, output, info);
	else if (is(tokens[special], "|"))
	{
		pipe(piped);
		switchboard(tokens, fd, piped[1], info);
		close(piped[1]);
		execute(&tokens[special + 1], piped[0], output, info);
		close(piped[0]);
	}
	else if (is(tokens[special], ">"))
	{
		new_output = redir(tokens[special + 1], &temp);
		switchboard(tokens, fd, new_output, info);
		close(new_output);
		info->status = temp;
	}
	else if (is(tokens[special], ">>"))
	{
		new_output = rredir(tokens[special + 1], &temp);
		switchboard(tokens, fd, new_output, info);
		close(new_output);
		info->status = temp;
	}
	else if (is(tokens[special], "<"))
	{
		new_output = left_redir(tokens[special + 1], &temp);
		if (new_output >= 0)
		{
			switchboard(tokens, new_output, output, info);
			close(new_output);
			info->status = temp;
		}
	}
	else
	{
		switchboard(tokens, fd, output, info);
		execute(&tokens[special + 1], fd, output, info);
	}
}

/*
** s_function is a version of an existing function that returns char * and
** possibly takes a piped fd
*/

/*
** switchboard() selects and executes a function
*/

void	switchboard(char **tokens, int fd, int output, t_info *info)
{
	(void) output;
	if (is(tokens[0], "echo"))
		info->status = ft_echo(tokens, output);
	else if (is(tokens[0], "pwd"))
		info->status = print_pwd(1);
	else if (is(tokens[0], "cd"))
		info->status = ft_cd(tokens);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens, info->status);
	else if (is(tokens[0], "export"))
		info->status = add_all_env(&(info->our_env), tokens);
	else if (is(tokens[0], "unset"))
		info->status = remove_all_env(&(info->our_env), tokens);
	else
		info->status = ft_exec(tokens, fd, output, info->our_env);
}
