/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:10:11 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/02 20:52:01 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** free_split() free()s an array of strings
*/

void	free_split(char **splitted)
{
	int i;

	i = 0;
	if (splitted == NULL)
		return ;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}

void	inthandler(int sig)
{
	g_kek = 0;
	if (g_flag == 1)
	{
		write(1, "\b\b  \b\b\n", 7);
		ft_putstr_fd(g_name, 1);
		write(1, "$ ", 2);
	}
	else
		write(1, "\n", 1);
	if (g_flag != 1)
		*g_status = 128 + sig;
	else
		*g_status = 1;
}

void	quit_handler(int sig)
{
	if (g_flag == 1)
		write(1, "\b\b  \b\b", 6);
	else
		write(1, "Quit: 3\n", 8);
	if (g_flag != 1)
		*g_status = 128 + sig;
	g_flag = 1;
}

void	ft_set_to_zero(int *i, int *quote, int *count, char *prev)
{
	*i = 0;
	*count = 0;
	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	*prev = '\0';
}

int		double_cond(char token)
{
	if (token == '$' || token == '`' || token == '"' || token == '\\' ||
											token == '\n')
		return (1);
	return (0);
}
