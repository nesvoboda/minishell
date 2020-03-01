/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:48:13 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 21:53:19 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	left_pipe(char **tokens, t_info *info, int tube[2], int fd)
{
	int io[2];

	g_flag = 0;
	close(tube[0]);
	info->is_forked = 1;
	io[0] = fd;
	io[1] = tube[1];
	recursive_madness(tokens, io, info, tokens);
	close(tube[1]);
	exit(0);
}


int		next_semi(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is(tokens[i], ";"))
			return (i);
		i++;
	}
	return (-1);
}

void	right_pipe(char **tokens, t_info *info, int tube[2], int output)
{
	int special;

	g_flag = 0;
	special = next_spec(tokens);
	close(tube[1]);
	info->is_forked = 1;
	if (special != -1)
		vpered(&tokens[special + 1], tube[0], output, info);
	exit(0);
}

void	main_piped_proc(char **tokens, pid_t pid[2], int tube[2], t_info *info)
{
	int status;
	int special;

	close(tube[0]);
	close(tube[1]);
	status = 0;
	special = next_semi(tokens);
	g_flag = 0;
	ft_wait_com(pid[1], status);
	ft_wait_com(pid[0], status);
	if (special != -1 && is(tokens[special], ";"))
		vpered(&tokens[special + 1], -1, 1, info);
}


void	actual_redir(char **tokens, t_info *info, int fd, int output)
{
	int io[2];
	int special;

	g_flag = 0;
	io[0] = fd;
	io[1] = output;
	special = next_spec(tokens);
	recursive_madness(tokens, io, info, tokens);
	if (special != -1)
		vpered(&tokens[special + 1], -1, 1, info);
}

void	handle_redirects(char **tokens, int fd, int output, t_info *info)
{
	int		special;
	int		tube[2];
	pid_t	pid[2];
	int		status;

	status = 0;
	special = next_spec(tokens);
	if (special > 0 && is(tokens[special], "|"))
	{
		pipe(tube);
		pid[0] = fork();
		if (pid[0] == 0)
			left_pipe(tokens, info, tube, fd);
		else
		{
			pid[1] = info->is_forked == 1 ? 0 : fork();
			if (pid[1] == 0)
			{
				right_pipe(tokens, info, tube, output);
				ft_wait_com(pid[0], 0);
				close(tube[0]);
			}
			else
				main_piped_proc(tokens, pid, tube, info);
		}
	}
	else
		actual_redir(tokens, info, fd, output);
}
