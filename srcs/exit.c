/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:02:34 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/02 18:05:06 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-' ||
									(str[i] == '+' && str[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

void	clean_quotes(char **tokens)
{
	int i;
	int spec;

	i = 0;
	spec = next_spec(tokens);
	if (spec == -1)
		spec = ft_tablen(tokens);
	while (i < spec)
	{
		tokens[i] = ft_copy_without_quotes(tokens[i]);
		i++;
	}
}

int		*io2(int *io, int fd1, int fd2)
{
	io[0] = fd1;
	io[1] = fd2;
	return (io);
}

void	ft_exit(char **tokens, int status, t_info *info)
{
	int		special;
	int		io[2];

	special = next_redir(tokens);
	clean_quotes(tokens);
	if (special != -1)
		recursive_madness(tokens, io2(io, -1, 1), info, 0);
	if (tokens[1] == NULL || is(tokens[1], "|"))
		status = info->status;
	else
		status = isnum(tokens[1]) ? ft_atoi(tokens[1]) : 255;
	if (!info->is_forked)
		write(1, "exit\n", 5);
	if (status == 255)
		error_handler(tokens[0], "numeric argument required", 255,
															info->program_name);
	else if (tokens[1] && tokens[2] && (special > 2 || special == -1))
	{
		error_handler(tokens[0], "too many arguments", -1,
															info->program_name);
		info->status = 1;
		return ;
	}
	exit((char)status);
}
