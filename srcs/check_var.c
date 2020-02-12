/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:28:41 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/12 17:14:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
char *ft_set_env(char *key, char **our_env)
{
	int i;
	char *cpy;

	i = 0;
	cpy = ft_strdup(key);
	while (cpy[i] != '\0' && cpy[i] != ' ' && cpy[i] != '\"')
		i++;
	cpy[i] = '\0';
	i = 0;
	while (our_env[i])
	{
		if (!ft_strncmp(our_env[i], cpy, find_equals(cpy)))
		{
			free(cpy);
			return (our_env[i]);
		}
		i++;
	}
	free(cpy);
	return (NULL);
}

void replace_var(char **tokens, char **our_env)
{
	char *new;

	if (find_env(our_env, &tokens[0][1]) < 0)
	{
		free(tokens[0]);
		tokens[0] = ft_strdup("");
	}
	else
	{
		new = ft_set_env(&tokens[0][1], our_env);
		while (*new != '=')
			new++;
		new++;
		free(tokens[0]);
		tokens[0] = ft_strdup(new);
	}
}

void replace_var_in_q(char **tokens, char **our_env)
{
	int i;
	char *env;
	char *new;
	int j;
	int k;

	k = 0;
	i = 0;
	j = 0;
	while (tokens[0][i] != '$' && tokens[0][i])
		i++;
	if (!tokens[0][i])
		return ;
	else
	{
		env = ft_set_env(&tokens[0][i + 1], our_env);
		new = malloc(sizeof(char) * (ft_strlen(env) + ft_strlen(tokens[0]) + 1));
		while (j < i)
		{
			new[j] = tokens[0][j];
			j++;
		}
		while (env[k] != '=' && env[k])
			k++;
		k++;
		while (env[k])
			new[j++] = env[k++];
		while (tokens[0][i] != '\"' && tokens[0][i] != ' ' && tokens[0][i])
			i++;
		while (tokens[0][i])
		{
			new[j++] = tokens[0][i];
			i++;
		}
		new[j] = '\0';
		free(tokens[0]);
		tokens[0] = new;
	}
}
void ft_check_token(char **tokens, char **our_env)
{
	if (tokens[0][0] == '$')
		replace_var(tokens, our_env);
	else if (tokens[0][0] == '\"')
		replace_var_in_q(tokens, our_env);
}

void check_var(char **tokens, char **our_env)
{
	int i;

	i = 0;
	while(tokens[i])
	{
		if (tokens[i][0] == '$' || tokens[i][0] == '\"')
			ft_check_token(&tokens[i], our_env);
		i++;
	}
}
