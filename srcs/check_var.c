/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:28:41 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/16 17:23:38 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	*stringify_status(int status)
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
	i = i + 2;
	while (env[k] != '=' && env[k])
		k++;
	k++;
	while (env[k])
		new[j++] = env[k++];
	while (tokens[i] != '\"' && tokens[i] != ' ' && tokens[i] &&
			tokens[i] != '$' && tokens[i] != '\'')
		i++;
	while (tokens[i])
	{
		new[j++] = tokens[i];
		i++;
	}
	new[j] = '\0';
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
			copy_var(new, tokens[0], env, i);
		free(tokens[0]);
		tokens[0] = new;
	}
}

void	ft_check_token(char **tokens, char **our_env, t_info *info, int i)
{
	char	prev;
	int		q;

	q = 0;
	prev = '\0';
	(void)info;
	(void)our_env;
	printf("%s\n", tokens[0]);
	while (tokens[0][i])
	{
		if (tokens[0][i] == '\'' && q == 0 && prev != '\\')
			q = 1;
		else if (tokens[0][i] == '\'' && q == 1 && prev != '\\')
			q = 0;
		prev = tokens[0][i];
		if (tokens[0][i] == '$' && prev != '\\' && q == 0)
		{
			replace_var(&tokens[0], our_env, info, i);
			printf("!!%s\n", tokens[0]);
			i = 0;
		}
		else if (tokens[0][0])
			i++;
	}
}

void	check_var(char **tokens, char **our_env, t_info *info)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		ft_check_token(&tokens[i], our_env, info, 0);
		i++;
	}
}
