/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:42:22 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/08 20:13:09 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** print_env() prints out a null-terminated string array, each string on its
** own line.
*/

void	print_env(char **our_env)
{
	int	i;

	i = 0;
	while (our_env[i])
	{
		ft_putstr(our_env[i++]);
		write(1, "\n", 1);
	}
}

int		find_equals(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (ft_strlen(str));
}

void	add_all_env(char ***our_env, char **tokens)
{
	int i;
	int stop;

	i = 1;
	stop = next_special(tokens);
	if (stop == -1)
		stop = ft_tablen(tokens);
	while (i < stop)
	{
		if (!find_env(*our_env, tokens[i]))
			add_env(our_env, tokens[i]);
		else
		{
			remove_env(our_env, tokens[i]);
			add_env(our_env, tokens[i]);
		}
		i++;
	}
}