/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:42:22 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 13:24:14 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int		check_key(char *str)
{
	return (find_equals(str) < ft_strlen(str));
}

void	invalid_identifier(char *token, char *command, int *status,
														char *program_name)
{
	ft_puterr(program_name);
	ft_puterr(": ");
	ft_puterr(command);
	ft_puterr(": `");
	ft_puterr(token);
	ft_puterr("': not a valid identifier\n");
	*status = 1;
}

int		detect_append(char **our_env, char *entry)
{
	int	i;

	if (entry[find_equals(entry)-1] == '+')
	{
		i = 0;
		while (our_env[i])
		{
			if (!ft_strncmp(our_env[i], entry, find_equals(our_env[i])))
				return (1);
			i++;
		}
	}
	return (0);
}

int		add_all_env(char ***our_env, char **tokens, int output, char *program_name)
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
		tokens[i] = ft_copy_without_quotes(tokens[i]);
		if (check_key(tokens[i]) && find_equals(tokens[i]) > 0)
		{
			if (detect_append(*our_env, tokens[i]))
				concat_env(our_env, tokens[i]);
			else if (find_env(*our_env, tokens[i]) < 0)
				add_env(our_env, tokens[i]);
			else
			{
				remove_env(our_env, tokens[i]);
				add_env(our_env, tokens[i]);
			}
		}
		else if (check_key(tokens[i]))
			invalid_identifier(tokens[i], "export", &status, program_name);
		i++;
	}
	if (tokens[1] == NULL)
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
