/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 14:30:57 by ablanar          ###   ########.fr       */
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

void	inthandler(int sig)
{
	g_kek = 0;
	if (g_flag == 1)
		write(1, "\b\b  \b\b\n> ", 9);
	else
		write(1, "\n", 1);
	if (g_line != NULL && g_flag)
	{
		free(g_line);
		g_line = malloc(sizeof(char) + 1);
		g_line[0] = '\0';
	}
	if (g_flag != 1)
		*g_status = 128 + sig;
	else
		*g_status = 1;
	g_flag = 1;
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
	if (token == '$' || token == '`' || token == '"' || token == '\\' || token == '\n')
		return (1);
	return (0);
}

int		ft_count_without_quotes(char *token)
{
	int		i;
	int		q[3];
	int		count;
	char	prev;

	i = 0;
	ft_set_to_zero(&i, q, &count, &prev);
	while (token[i])
	{
		if ((token[i] != '\'' || (q[2] > 0|| q[1])) && (token[i] != '"' || (q[2] > 0 || q[0]))  && (token[i] != '\\' || (q[2] > 0 || q[0] || (q[1] && !double_cond(token[i + 1])))))
			count++;
		else if (token[i] == '\\' && (double_cond(token[i + 1])) && q[1] != 0 && q[2] == 0 && q[0] != 1)
			count++;
		if ((token[i] == '\'' || token[i] == '"' || token[i] == '\\') && q[2] == 0)
			set_quotes(&token[i], q, i);
		if (q[2] != i + 1)
			q[2] = 0;
		i++;
	}
	return (count);
}

void	copy_without(char *token, char *new, int *q, char prev)
{
	int i;
	int j;

	prev = '\0';
	i = 0;
	j = 0;
	while (token[i])
	{
		if ((token[i] != '\'' || (q[2] > 0|| q[1])) && (token[i] != '"' || (q[2] > 0 || q[0])) && (token[i] != '\\' || (q[2] > 0 || q[0] || (q[1] && !double_cond(token[i + 1])))))
			new[j++] = token[i];
		else if (token[i] == '\\' && (double_cond(token[i + 1])) && q[1] != 0 && q[2] == 0 && q[0] != 1)
		{
			i++;
			new[j] = token[i];
			j++;
		}
		else if ((token[i] == '\'' || token[i] == '"' || token[i] == '\\') && q[2] == 0)
			set_quotes(&token[i], q, i);
		if (q[2] != i + 1)
			q[2] = 0;
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
		// while (com[i])
		// {
		// 	printf("*%s*\n", com[i]);
		// 	i++;
		// }
		// i = 0;
		com = vpered(com, -1, 1, info);
		if (com[0])
			free_split(com);
		else
			free(com);
	}
}
