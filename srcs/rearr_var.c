/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearr_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:23:08 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 18:20:48 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*stringify_status(int status)
{
	char *ret;

	ret = ft_itoa(status);
	ret[0] = '=';
	return (ret);
}

void	copy_var(char *new, char *tokens, char *env, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (j < i)
	{
		new[j] = tokens[j];
		j++;
	}
	i++;
	while (env[k] != '=' && env[k])
		k++;
	k++;
	while (env[k])
		new[j++] = env[k++];
	while (tokens[i] != '\"' && tokens[i] != ' ' && tokens[i] && tokens[i]
		!= '=' && tokens[i] != '$' && tokens[i] != '\'' && tokens[i] != '?')
		i++;
	if (tokens[i] == '?')
		i++;
	while (tokens[i])
		new[j++] = tokens[i++];
	new[j] = '\0';
}

#include <stdio.h>
void	replace_var_helper(char *env, char *token)
{
	printf("%s\n", token);
	if (token[0] == '?')
		free(env);
}

void	replace_var(char **tokens, char **our_env, t_info *info, int i)
{
	char	*env;
	char	*new;
	char	*empty;

	if (!tokens[0][i])
		return ;
	else
	{
		env = ft_set_env(&tokens[0][i + 1], our_env, *info);
		if (!(new = malloc(sizeof(char) *
			(ft_strlen(env) + ft_strlen(tokens[0]) + 1))))
			exit(1);
		if (env == NULL)
		{
			empty = ft_strdup("=");
			copy_var(new, tokens[0], empty, i);
			free(empty);
		}
		else
		{
			copy_var(new, tokens[0], env, i);
			replace_var_helper(env, &tokens[0][i + 1]);
		}
		free(tokens[0]);
		tokens[0] = new;
	}
}

void	ft_rearr(char ***nach, char **new, int n)
{
	int		i;
	char	**cpy;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i = 0;
	if (!(cpy = malloc(sizeof(char *) * (ft_tablen(*nach)
			+ ft_tablen(new) + 1))))
		return ;
	while (i < n)
		cpy[k++] = ft_strdup(*nach[i++]);
	while (new[j])
		cpy[k++] = ft_strdup(new[j++]);
	while (nach[0][i + 1] != NULL)
	{
		cpy[k++] = ft_strdup(nach[0][i + 1]);
		i++;
	}
	cpy[k] = NULL;
	free_split(*nach);
	free_split(new);
	nach[0] = cpy;
}
