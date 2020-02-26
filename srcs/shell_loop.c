/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/26 17:53:12 by ablanar          ###   ########.fr       */
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
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
}
#include <stdio.h>
void	inthandler(int sig)
{
	if (g_flag == 1)
		write(1, "\b\b  \b\b\n> ", 9);
	else
		write(1, "\n", 1);
	g_flag = 1;
	*g_status = 128 + sig;
}

void	quit_handler(int sig)
{
	if (g_flag == 1)
		write(1, "\b\b  \b\b", 6);
	else
		write(1, "Quit: 3\n", 8);
	g_flag = 1;
	*g_status = 128 + sig;

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

int		ft_count_without_quotes(char *token)
{
	int		i;
	int		quote[3];
	int		count;
	char	prev;

	i = 0;
	ft_set_to_zero(&i, quote, &count, &prev);
	while (token[i])
	{
		if (token[i] == '\"' && quote[1] == 0 && prev != '\\')
			quote[0] = 1;
		else if (token[i] == '\"' && quote[0] == 1 && quote[1] == 0 &&
				prev != '\\')
			quote[0] = 0;
		if (token[i] == '\'' && quote[0] == 0 && prev != '\\')
			quote[1] = 1;
		else if (token[i] == '\'' && quote[0] == 0 && quote[1] == 1
			&& prev != '\\')
			quote[1] = 0;
		if (!((token[i] == '\'' && quote[0] != 1) || (token[i] == '"' && quote[1] != 1  && prev != '\\') || (token[i] == '\\')) || (token[i] == '\\' && quote[1] == 1) || (token[i] == '\'' && prev == '\\'))
			count++;
		if (token[i] == '\\' && (token[i + 1] == '$' || token[i + 1] == '`' || token[i + 1] == '"' || token[i + 1] == '\\' || token[i + 1] == '\n') && quote[0] == 1 && prev != '\\')
			count++;
		// if (!(((token[i] == '\'' && quote[0] != 1) || (token[i] == '\"'
		// 	&& quote[1] != 1) || token[i] == '\\') && (prev != '\\')) || (token[i] == '\\' && quote[1] == 1))
		// 	count++;
		prev = token[i];
		i++;
	}
	return (count);
}

void	copy_without(char *token, char *new, int *quote, char prev)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\"' && quote[1] == 0 && quote[0] != 1
				&& prev != '\\')
			quote[0] = 1;
		else if (token[i] == '\"' && quote[0] == 1 && quote[1] == 0 &&
				prev != '\\')
			quote[0] = 0;
		if (token[i] == '\'' && quote[0] == 0 && quote[1] != 1 && prev != '\\')
			quote[1] = 1;
		else if (token[i] == '\'' && quote[0] == 0 && quote[1] == 1)
			quote[1] = 0;
		if (!((token[i] == '\'' && quote[0] != 1) || (token[i] == '"' && quote[1] != 1) || (token[i] == '\\')) || (token[i] == '\\' && quote[1] == 1) || (token[i] == '\'' && prev == '\\' && !(j != 0 && new[j - 1] == '\\' && token[i] == '\'')))
			new[j++] = token[i];
		// if (!((((token[i] == '\'' && quote[0] != 1) || (token[i] == '\"'
		// 	&& quote[1] != 1) || token[i] == '\\') && (prev != '\\')) || (j != 0 && new[j - 1] == '\\' && token[i] == '\'')) || (token[i] == '\\' && quote[1] == 1))
		if (token[i] == '\\' && (token[i + 1] == '$' || token[i + 1] == '`' || token[i + 1] == '"' || token[i + 1] == '\\' || token[i + 1] == '\n') && quote[0] == 1 && prev != '\\')
		{
			i++;
			new[j++] = token[i];
		}
		prev = token[i];
		i++;
	}
	new[j] = '\0';
}

char	*ft_copy_without_quotes(char *token)
{
	int		quote[3];
	char	*new;
	char	prev;

	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	prev = '\0';
	if (!(new = malloc(sizeof(char) * ft_count_without_quotes(token) + 1)))
		return (NULL);
	copy_without(token, new, quote, prev);
	free(token);
	return (new);
}

char 	**vpered(char **com, int fd, int output, t_info *info)
{
	check_var(&com, info->our_env, info);
	if (com[0] != NULL)
		com[0] = ft_copy_without_quotes(com[0]);
	if (com[0] != NULL)
		execute(com, fd, output, info);
	return (com);
}

void	shell_loop_2(t_info *info)
{
	char	**com;
	int		i;

	i = 0;
	info->last_char = 0;
	while (1)
	{
		g_flag = 1;
		signal(SIGINT, inthandler);
		signal(SIGQUIT, quit_handler);
		write(1, "> ", 2);
		com = ft_get_command(info);
		while (com[i])
		{
			printf("*%s*\n", com[i]);
			i++;
		}
		i = 0;
		com = vpered(com, -1, 1, info);
		if (com[0])
			free_split(com);
		else
			free(com);
	}
}
