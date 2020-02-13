/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:28:41 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/13 18:14:46 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char *stringify_status(int status)
{
	char *ret;

	ret = malloc(sizeof(char) * 3);
	ret[0] = '=';
	if (status == 0)
		ret[1] = '0';
	else
		ret[1] = '1';
	ret[2] = '\0';
	return (ret);
}

char *ft_set_env(char *key, char **our_env, t_info info)
{
	int i;
	char *cpy;

	i = 0;
	cpy = ft_strdup(key);
	while (cpy[i] != '\0' && cpy[i] != ' ' && cpy[i] != '\"')
		i++;
	cpy[i] = '\0';
	i = 0;
	if (!ft_strncmp(cpy, "?", ft_strlen(cpy)))
		return (stringify_status(info.status));
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

void replace_var(char **tokens, char **our_env, t_info info)
{
	char *new;

	if (find_env(our_env, &tokens[0][1]) < 0 && !is(tokens[0], "$?"))
	{
		free(tokens[0]);
		tokens[0] = ft_strdup("");
	}
	else
	{
		new = ft_set_env(&tokens[0][1], our_env, info);
		while (*new != '=')
			new++;
		new++;
		free(tokens[0]);
		tokens[0] = ft_strdup(new);
	}
}

void replace_var_in_q(char **tokens, char **our_env, t_info *info)
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
		env = ft_set_env(&tokens[0][i + 1], our_env, *info);
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

void ft_check_token(char **tokens, char **our_env, t_info *info)
{
	if (tokens[0][0] == '$')
		replace_var(tokens, our_env, *info);
	else if (tokens[0][0] == '\"')
		replace_var_in_q(tokens, our_env, info);
}

void check_var(char **tokens, char **our_env, t_info *info)
{
	int i;

	i = 0;
	while(tokens[i])
	{
		if (tokens[i][0] == '$' || tokens[i][0] == '\"')
			ft_check_token(&tokens[i], our_env, info);
		i++;
	}
}
