/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:02:34 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 13:41:50 by ashishae         ###   ########.fr       */
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
									str[i] == '+'))
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

void	ft_exit(char **tokens, int status, t_info *info)
{
	char	ret;
	int		special;

	special = next_redir(tokens);
	clean_quotes(tokens);
	if (special != -1)
		recursive_madness(tokens, -1, 1, info, 0);
	if (tokens[1] == NULL || is(tokens[1], "|"))
		status = 0;
	else if (isnum(tokens[1]))
		status = ft_atoi(tokens[1]);
	else
		status = 255;
	if (!info->is_forked)
		write(1, "exit\n", 5);
	if (status == 255)
		error_handler(tokens[0], ": numeric argument required", 255,
															info->program_name);
	else if (tokens[1] && tokens[2] && (special > 2 || special == -1))
	{
		error_handler(tokens[0], ": too many arguments", -1,
															info->program_name);
		info->status = 1;
		return ;
	}
	ret = (char)status;
	exit(ret);
}
