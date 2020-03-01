/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:08:47 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 19:43:17 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
void	handle_redirects(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int tube[2];
	pid_t	pid;
	pid_t	pid2;
	int status;
	int	io[2];

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
			io[0] = fd;
			io[1] = tube[1];
			recursive_madness(tokens, io, info, tokens);
			close(tube[1]);
			exit(0);
		}
		else
		{
			pid2 = info->is_forked == 1 ? 0 : fork();
			if (pid2 == 0)
			{
				close(tube[1]);
				info->is_forked = 1;
				// io[0] = tube[0];
				// io[1] = output;
				vpered(&tokens[special + 1], tube[0], output, info);
				ft_wait_com(pid, status);
				close(tube[0]);
			}
			else
			{
				close(tube[0]);
				close(tube[1]);
				special = special + next_spec(&tokens[special + 1]) + 1;
				printf("g_flag was %d\n", g_flag);
				g_flag = 0;
				ft_wait_com(pid2, status);
				ft_wait_com(pid, status);
				if (special != -1 && is(tokens[special], ";"))
					vpered(&tokens[special + 1], tube[0], output, info);
			}
		}
	}
	else
	{
		io[0] = fd;
		io[1] = output;
		recursive_madness(tokens, io, info, tokens);
		if (special != -1)
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

int check_last_fd(char **tokens, int *status)
{
	int i;

	i = 0;

	while (tokens[i] && !is(tokens[i], ";") && !is(tokens[i], "|"))
		i++;
	i--;
	if (is(tokens[i], "<") || is(tokens[i], ">>") || is(tokens[i], ">"))
	{
		syntax_error(tokens[i+1], status);
		return (-1);
	}
	if (tokens && tokens[i+1] && tokens[i+2])
		return (check_last_fd(&tokens[i+2], status));
	return (0);
}


void	close_fds(int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 1)
		close(fd2);
}

/*
** io[2] is an array that contains 2 fds. io[0] is input fd, io[1] is output fd.
*/

void recursive_madness(char **tokens, int io[2], t_info *info,
														char **token_nachalo)
{
	int special;
	int special2;
	int our_io[2];

	our_io[0] = io[0];
	our_io[1] = io[1];
	special = next_redir(tokens);
	special2 = special + next_redir(&tokens[special + 1]) + 1;
	if (!is(tokens[special], "|"))
		special2 = special + next_redir(&tokens[special + 1]) + 1;
	else
		special2 = special;
	if (is(tokens[special], ">"))
		if ((io[1] = handle_right_redir(tokens, io[0], info)) < 0)
			return ;
	if (is(tokens[special], ">>"))
		if ((io[1] = handle_right_rredir(tokens, io[0], special, info)) < 0)
			return ;
	if (is(tokens[special], "<"))
		if ((io[0] = handle_left_redir(tokens, io[1], info)) < 0)
			return ;
	our_io[0] = io[0];
	our_io[1] = io[1];
	if (special2 == special && token_nachalo != NULL && tokens[special + 1])
	{
		switchboard(token_nachalo, io[0], io[1], info);
		close_fds(our_io[0], our_io[1]);
	}
	else if (tokens[special + 1] != NULL && tokens[special + 2] != NULL)
	{
		
		recursive_madness(&tokens[special + 1], io, info, token_nachalo);
		close_fds(our_io[0], our_io[1]);
	}
	
}