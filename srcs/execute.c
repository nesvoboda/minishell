/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:12:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/27 21:46:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define DEF_FD -1
#include <stdio.h>
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
	int i;
	int spec;

	i = 0;
	if (tokens[0] == NULL)
		return ;
	special = next_special(tokens);
	spec = next_spec(tokens);
	if (special == -1)
		switchboard(tokens, fd, output, info);
	else if (((tokens[special + 1] == NULL) || is_special(tokens[special + 1])
			== 1) && !is(tokens[special], "|") && (!is(tokens[special], ";") || (tokens[special + 1] != NULL && is_special(tokens[special + 1]))))
	{
		if (is(tokens[special], ";") && tokens[special + 1] != NULL && is(tokens[special + 1], ";"))
			syntax_error(";;", &info->status);
		else
			syntax_error(tokens[special + 1], &info->status);
	}
	else if ((special == 0) && (is(tokens[special], ";") || is(tokens[special], "|")))
		syntax_error(tokens[special], &info->status);
	else if ((spec > 0 && is(tokens[spec], "|")) || is(tokens[special], ">") ||
		is(tokens[special], ">>") || is(tokens[special], "<"))
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

void	switchboard(char **tokens, int fd, int output, t_info *info)
{
	int temp;

	if (is(tokens[0], "echo"))
		info->status = ft_echo(tokens, output);
	else if (is(tokens[0], "pwd"))
		info->status = print_pwd(output);
	else if (is(tokens[0], "cd"))
		info->status = ft_cd(tokens, info->our_env);
	else if (is(tokens[0], "exit"))
		ft_exit(tokens, info->status, info);
	else if (is(tokens[0], "export"))
		info->status = add_all_env(&(info->our_env), tokens, output);
	else if (is(tokens[0], "unset"))
		info->status = remove_all_env(&(info->our_env), tokens);
	else
	{
		temp = ft_exec(tokens, fd, output, info);
		if (g_flag != 1 && info->is_forked != 1)
			info->status = temp;
	}
}
