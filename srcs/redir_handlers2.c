/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:32:03 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 16:09:07 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(char **tokens, int fd, int output, t_info *info)
{
	int piped[2];
	int special;

	special = next_special(tokens);
	pipe(piped);
	switchboard(tokens, fd, piped[1], info);
	close(piped[1]);
	vpered(&tokens[special + 1], piped[0], output, info);
	close(piped[0]);
}

int		handle_left_redir(char **tokens, int output, t_info *info)
{
	int new_output;
	int temp;
	int special;

	(void)output;
	special = next_special(tokens);
	if (tokens[special + 1] == NULL)
	{
		syntax_error(tokens[special + 1], &info->status);
		return (-1);
	}
	else
		new_output = left_redir(tokens[special + 1], &temp, info->program_name);
	info->status = temp;
	return (new_output);
}

int		handle_right_redir(char **tokens, int fd, t_info *info)
{
	int new_output;
	int temp;
	int special;

	(void)fd;
	special = next_special(tokens);
	if (tokens[special + 1] == NULL)
	{
		syntax_error(tokens[special + 1], &info->status);
		return (-1);
	}
	else
		new_output = redir(tokens[special + 1], &temp, info->program_name);
	info->status = temp;
	return (new_output);
}

int		handle_right_rredir(char **tokens, int fd, int special, t_info *info)
{
	int new_output;
	int temp;

	(void)fd;
	if (tokens[special + 1] == NULL)
	{
		syntax_error(tokens[special + 1], &info->status);
		return (-1);
	}
	else
		new_output = rredir(tokens[special + 1], &temp, info->program_name);
	info->status = temp;
	return (new_output);
}
