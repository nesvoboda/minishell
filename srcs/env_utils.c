/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:42:22 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/28 17:11:04 by ablanar          ###   ########.fr       */
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

void	invalid_identifier(char *token, char *command, int *status)
{
	ft_puterr("our sh: ");
	ft_puterr(command);
	ft_puterr(": `");
	ft_puterr(token);
	ft_puterr("': not a valid identifier\n");
	*status = 1;
}

int		detect_append(char **our_env, char *entry)
{
	int	i;

	if (entry[find_equals(entry) - 1] == '+')
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

void	add_env_helper(char ***our_env, char **tokens, int *status)
{
	tokens[0] = ft_copy_without_quotes(tokens[0]);
	if (check_key(tokens[0]) && find_equals(tokens[0]) > 0)
	{
		if (detect_append(*our_env, tokens[0]))
			concat_env(our_env, tokens[0]);
		else if (find_env(*our_env, tokens[0]) < 0)
			add_env(our_env, tokens[0]);
		else
		{
			remove_env(our_env, tokens[0]);
			add_env(our_env, tokens[0]);
		}
	}
	else if (check_key(tokens[0]))
		invalid_identifier(tokens[0], "export", status);
}
