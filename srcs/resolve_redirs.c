/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:08:47 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/02 16:32:07 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		next_redir(char **tokens)
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

int		check_last_fd(char **tokens, int *status)
{
	int i;

	i = 0;
	while (tokens[i] && !is(tokens[i], ";") && !is(tokens[i], "|"))
		i++;
	if (i != 0)
		i--;
	if (is(tokens[i], "<") || is(tokens[i], ">>") || is(tokens[i], ">"))
	{
		syntax_error(tokens[i + 1], status);
		return (-1);
	}
	if (tokens && tokens[i + 1] && tokens[i + 2])
		return (check_last_fd(&tokens[i + 2], status));
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

void	recursive_madness(char **tokens, int io[2], t_info *info,
														char **token_nachalo)
{
	int special;
	int special2;
	int our_io[2];

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
	io2(our_io, io[0], io[1]);
	if (special2 == special && token_nachalo != NULL && tokens[special + 1])
		switchboard(token_nachalo, io[0], io[1], info);
	else if (tokens[special + 1] != NULL && tokens[special + 2] != NULL)
		recursive_madness(&tokens[special + 1], io, info, token_nachalo);
	close_fds(our_io[0], our_io[1]);
}
