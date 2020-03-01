/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 18:28:50 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define DEF_FD -1

/*
** execute() returns the result of the evaluation of tokens, passing an fd
** to any function it will launch
*/

void	syntax_error(char *error, int *status)
{
	write(2, "syntax error near unexpected token `", 36);
	if (error == NULL)
		write(2, "newline", 7);
	else
		write(2, error, ft_strlen(error));
	write(2, "\'\n", 2);
	*status = 258;
}

void	execute(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int spec;

	if (tokens[0] == NULL)
		return ;
	special = next_special(tokens);
	spec = next_spec(tokens);
	if (special == -1)
		switchboard(tokens, fd, output, info);
	else if (error_bool(tokens[special], tokens[special + 1]))
	{
		if (error_bool2(tokens[special], tokens[special + 1]))
			syntax_error(";;", &info->status);
		else
			syntax_error(tokens[special + 1], &info->status);
	}
	else if (!special && (is(tokens[special], ";") || is(tokens[special], "|")))
		syntax_error(tokens[special], &info->status);
	else if ((spec > 0 && is(tokens[spec], "|")) || redir_bool(tokens[special]))
		handle_redirects(tokens, fd, output, info);
	else
	{
		switchboard(tokens, fd, output, info);
		vpered(&tokens[spec + 1], -1, 1, info);
	}
}

/*
** s_function is a version of an existing function that returns char * and
** possibly takes a piped fd
*/

/*
** switchboard() selects and executes a function
*/
#include <stdio.h>
void	switchboard(char **tokens, int fd, int output, t_info *info)
{
	int temp;

	if (is(tokens[0], "echo"))
		info->status = ft_echo(tokens, output);
	else if (is(tokens[0], "pwd"))
		info->status = print_pwd(output);
	else if (is(tokens[0], "cd"))
		info->status = ft_cd(tokens, info->our_env, info->program_name);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens, info->status, info);
	else if (is(tokens[0], "export"))
		info->status = add_all_env(&(info->our_env), tokens, output,
														info->program_name);
	else if (is(tokens[0], "unset"))
		info->status = remove_all_env(&(info->our_env), tokens,
															info->program_name);
	else
	{
		temp = ft_exec(tokens, fd, output, info);
		if (g_flag != 1 && info->is_forked != 1)
			info->status = temp;
	}
}
