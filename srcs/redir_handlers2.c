/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:32:03 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 15:46:25 by ashishae         ###   ########.fr       */
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

#include <stdio.h>

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
	// int special;
	// int special2;

	// printf("Last fd\n");
	// special = next_redir(tokens);
	// special2 = next_redir(&tokens[special+1]);
	// if (special2 < 0)
	// 	special2 = special;
	// while (special2 != special)
	// {
	// 	special = special2;
	// 	if (!tokens[special+1] || special2 < 0)
	// 		special2 = special;
	// 	else
	// 		special2 = next_redir(&tokens[special+1]);
	// }
	// if (!tokens[special2 + 1])
	// 	return (-1);
	return (0);
}

void recursive_madness(char **tokens, int fd, int output, t_info *info, char **token_nachalo)
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
	if (special2 == special && token_nachalo != NULL && tokens[special + 1] != NULL)
	{
		printf("Switchboard on %s\n", tokens[0]);
		switchboard(token_nachalo, fd, output, info);
	}
	else if (tokens[special + 1] != NULL && tokens[special + 2] != NULL)
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

int	handle_right_redir(char **tokens, int fd, t_info *info)
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

int	handle_right_rredir(char **tokens, int fd, int special, t_info *info)
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
