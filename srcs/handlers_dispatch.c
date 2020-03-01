/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:48:13 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 20:37:18 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
void 	left_pipe(char **tokens, t_info *info, int tube[2], int fd)
{
	int io[2];

	close(tube[0]);
	info->is_forked = 1;
	io[0] = fd;
	io[1] = tube[1];
	recursive_madness(tokens, io, info, tokens);
	close(tube[1]);
	exit(0);
}

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
			left_pipe(tokens, info, tube, fd);
		}
		else
		{
			pid2 = info->is_forked == 1 ? 0 : fork();
			if (pid2 == 0)
			{
				close(tube[1]);
				info->is_forked = 1;
				vpered(&tokens[special + 1], tube[0], output, info);
				ft_wait_com(pid, status);
				close(tube[0]);
			}
			else
			{
				close(tube[0]);
				close(tube[1]);
				special = special + next_spec(&tokens[special + 1]) + 1;
				g_flag = 0;
				printf("%d\n", special);
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
