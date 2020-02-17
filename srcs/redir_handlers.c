/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:32:03 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/17 15:34:54 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(char **tokens, int fd, int output, t_info *info)
{
	int piped[2];
	int special;

	special = next_special(tokens);
	pipe(piped);
	switchboard(tokens, fd, piped[1], info);
	close(piped[1]);
	execute(&tokens[special + 1], piped[0], output, info);
	close(piped[0]);
}

void	handle_left_redir(char **tokens, int output, t_info *info)
{
	int new_output;
	int temp;
	int special;

	special = next_special(tokens);
	new_output = left_redir(tokens[special + 1], &temp);
	if (new_output >= 0)
	{
		switchboard(tokens, new_output, output, info);
		close(new_output);
		info->status = temp;
	}
}

void	handle_right_redir(char **tokens, int fd, t_info *info)
{
	int new_output;
	int temp;
	int special;

	special = next_special(tokens);
	new_output = redir(tokens[special + 1], &temp);
	switchboard(tokens, fd, new_output, info);
	close(new_output);
	info->status = temp;
}

void	handle_right_rredir(char **tokens, int fd, int special, t_info *info)
{
	int new_output;
	int temp;

	new_output = rredir(tokens[special + 1], &temp);
	switchboard(tokens, fd, new_output, info);
	close(new_output);
	info->status = temp;
}
