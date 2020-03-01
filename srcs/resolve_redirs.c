/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:08:47 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 16:14:42 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redirects(char **tokens, int fd, int output, t_info *info)
{
	int special;
	int tube[2];
	pid_t	pid;
	pid_t	pid2;
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
			pid2 = fork();
			if (pid2 == 0)
			{
				close(tube[1]);
				info->is_forked = 1;
				recursive_madness(&tokens[special + 1], tube[0], output, info, &tokens[special + 1]);
				ft_wait_com(pid, status);
				close(tube[0]);
			}
			else
			{
				if (special != -1)
				close(tube[0]);
				close(tube[1]);
				special = next_spec(&tokens[special + 1]);
				ft_wait_com(pid2, status);
				ft_wait_com(pid, status);
				if (special != -1)
					vpered(&tokens[special + 1], tube[0], output, info);
			}
		}
	}
	else
	{
		recursive_madness(tokens, fd, output, info, tokens);
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

void recursive_madness(char **tokens, int fd, int output, t_info *info,
														char **token_nachalo)
{
	int special;
	int special2;

	special = next_redir(tokens);
	special2 = special + next_redir(&tokens[special + 1]) + 1;
	if (!is(tokens[special], "|"))
		special2 = special + next_redir(&tokens[special + 1]) + 1;
	else
		special2 = special;
	if (is(tokens[special], ">"))
		if ((output = handle_right_redir(tokens, fd, info)) < 0)
			return ;
	if (is(tokens[special], ">>"))
		if ((output = handle_right_rredir(tokens, fd, special, info)) < 0)
			return ;
	if (is(tokens[special], "<"))
		if ((fd = handle_left_redir(tokens, output, info)) < 0)
			return ;
	if (special2 == special && token_nachalo != NULL && tokens[special + 1] != NULL)
		switchboard(token_nachalo, fd, output, info);
	else if (tokens[special + 1] != NULL && tokens[special + 2] != NULL)
		recursive_madness(&tokens[special + 1], fd, output, info, token_nachalo);
	if (fd > 0)
		close(fd);
	if (output > 1)
		close(output);
}