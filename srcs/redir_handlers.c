/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:32:03 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/19 20:51:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
void	handle_redirects(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int tube[2];
	pid_t	pid;
	int status;

	status = 0;
	special = next_spec(tokens);
	if (special > 0 && is(tokens[special], "|"))
	{
		pipe(tube);
		pid = fork();
		if (pid == 0)
		{
			close(tube[0]);
			info->is_forked = 1;
			recursive_madness(tokens, fd, tube[1], info, tokens);
			close(tube[1]);
			exit(0);
		}
		else
		{
			printf("Dpchka v pipe: %d\n", pid);
			close(tube[1]);
			vpered(&tokens[special + 1], tube[0], output, info);
			ft_wait_com(pid, status);
			close(tube[0]);
		}
	}
	else
	{
		recursive_madness(tokens, fd, output, info, tokens);
		vpered(&tokens[special + 1], -1, 1, info);
	}
}

int next_redir(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is(tokens[i], "|") || is(tokens[i], "<") ||
			 is(tokens[i], ">>") || is(tokens[i], ">"))
			return (i);
		i++;
	}
	return (-1);
}

void recursive_madness(char **tokens, int fd, int output, t_info *info, char **token_nachalo)
{
	int special;
	int special2;

	special = next_redir(tokens);
	if (is(tokens[special], ">"))
	{
		output = handle_right_redir(tokens, fd, info);
		if (output < 0)
			return ;
	}
	if (is(tokens[special], ">>"))
	{
		output = handle_right_rredir(tokens, fd, special, info);
		if (output < 0)
			return ;
	}
	if (is(tokens[special], "<"))
	{
		fd = handle_left_redir(tokens, output, info);
		if (fd < 0)
			return ;
	}
	special2 = special + next_redir(&tokens[special + 1]) + 1;
	if (special2 == special)
		switchboard(token_nachalo, fd, output, info);
	else
		recursive_madness(&tokens[special + 1], fd, output, info, token_nachalo);
	if (fd > 0)
		close(fd);
	if (output > 1)
		close(output);
}

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

int	handle_left_redir(char **tokens, int output, t_info *info)
{
	int new_output;
	int temp;
	int special;
	(void)output;
	special = next_special(tokens);
	new_output = left_redir(tokens[special + 1], &temp);
	if (new_output >= 0)
	{
		info->status = temp;
		return (new_output);
	}
	return (-10);
}

int	handle_right_redir(char **tokens, int fd, t_info *info)
{
	int new_output;
	int temp;
	int special;

	(void)fd;
	special = next_special(tokens);
	new_output = redir(tokens[special + 1], &temp);
	info->status = temp;
	return (new_output);
}

int	handle_right_rredir(char **tokens, int fd, int special, t_info *info)
{
	int new_output;
	int temp;

	(void)fd;
	new_output = rredir(tokens[special + 1], &temp);
	info->status = temp;
	return (new_output);
}
