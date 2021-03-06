/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:06:41 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 13:34:58 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		add_all_env(char ***our_env, char **tokens, int output,
															char *program_name)
{
	int i;
	int stop;
	int status;

	i = 1;
	status = 0;
	stop = next_special(tokens);
	stop = stop < 0 ? ft_tablen(tokens) : stop;
	while (i < stop)
	{
		add_env_helper(our_env, &tokens[i], &status, program_name);
		i++;
	}
	if (tokens[1] == NULL || is_special(tokens[1]))
		env_noarg(*our_env, output);
	return (status);
}

int		remove_all_env(char ***our_env, char **tokens, char *program_name)
{
	int i;
	int stop;
	int status;

	i = 1;
	status = 0;
	stop = next_special(tokens);
	if (stop == -1)
		stop = ft_tablen(tokens);
	while (i < stop)
	{
		tokens[i] = ft_copy_without_quotes(tokens[i]);
		if (check_key(tokens[i]))
			invalid_identifier(tokens[i], "unset", &status, program_name);
		else if (find_env(*our_env, tokens[i]) > 0)
			remove_env(our_env, tokens[i]);
		i++;
	}
	return (status);
}
