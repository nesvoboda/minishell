/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/16 18:29:58 by ablanar          ###   ########.fr       */
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

void	syntax_error(char *error)
{
	write(2, "syntax error near unexpected token `", 36);
	if (error == NULL)
		write(2, "newline", 7);
	else
		write(2, error, ft_strlen(error));
	write(2, "\'\n", 2);
}

void	execute(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int piped[2];
	int new_output;
	int	temp;

	if (tokens[0] == NULL)
		return ;
	special = next_special(tokens);
	if (special == -1)
		switchboard(tokens, fd, output, info);
	else if ((tokens[special + 1] == NULL || is_special(tokens[special + 1])
			== 1) && !is(tokens[special], ";"))
		syntax_error(tokens[special + 1]);
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
	if (is(tokens[0], "echo"))
		info->status = ft_echo(tokens, output);
	else if (is(tokens[0], "pwd"))
		info->status = print_pwd(1);
	else if (is(tokens[0], "cd"))
		info->status = ft_cd(tokens, info->our_env);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens, info->status);
	else if (is(tokens[0], "export"))
		info->status = add_all_env(&(info->our_env), tokens);
	else if (is(tokens[0], "unset"))
		info->status = remove_all_env(&(info->our_env), tokens);
	else
		info->status = ft_exec(tokens, fd, output, info->our_env);
}
