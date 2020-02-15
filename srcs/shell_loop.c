/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/15 15:46:55 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Remove before flight
#include <stdio.h>
#include <string.h>
#include <signal.h>
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

void  INThandler(int sig)
{
     // char  c;
	 (void)sig;

	 // signal(SIGINT, INThandler);

	 // signal(SIGINT, INThandler);
     // printf("OUCH, did you hit Ctrl-C?\n"
     //        "Do you really want to quit? [y/n] ");
     // c = getchar();
     // if (c == 'y' || c == 'Y')ma
     //      exit(0);
     // else
     g_fd = 0;
     write (1, "\n> ", 3);
     // signal(SIGINT, INThandler);
     // getchar(); // Get new line character
     // shell_loop_2();
}

void  quit_handler(int sig)
{
	(void)sig;
}

int ft_count_without_quotes(char *token)
{
	int i;
	int quote[2];
	int count;
	char prev;

	i = 0;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	prev ='\0';
	while (token[i])
	{
		if (token[i] == '\"' && quote[1] == 0 && prev != '\\')
			quote[0] = 1;
		else if (token[i] == '\"' && quote[0] == 1 && quote[1] == 0 && prev != '\\')
			quote[0] = 0;
		if (token[i] == '\'' && quote[0] == 0 && prev != '\\')
			quote[1] = 1;
		else if (token[i] == '\'' && quote[0] == 0 && quote[1] == 1 && prev != '\\')
			quote[1] = 0;
		if (!(((token[i] == '\'' && quote[0] != 1) || (token[i] == '\"' && quote[1] != 1) || token[i] == '\\') && prev != '\\'))
			count++;
		prev = token[i];
		i++;
	}
	return (count);
}

char *ft_copy_without_quotes(char *token)
{
	int i;
	int quote[2];
	char *new;
	int j;
	char prev;

	i = 0;
	j = 0;
	prev = '\0';
	if (!(new = malloc(sizeof(char) * ft_count_without_quotes(token) + 1)))
		return (NULL);
	quote[0] = 0;
	quote[1] = 0;
	while (token[i])
	{
		if (token[i] == '\"' && quote[1] == 0 && quote[0] != 1 && prev != '\\')
			quote[0] = 1;
		else if (token[i] == '\"' && quote[0] == 1 && quote[1] == 0 && prev != '\\')
			quote[0] = 0;
		if (token[i] == '\'' && quote[0] == 0 && quote[1] != 1 && prev != '\\')
			quote[1] = 1;
		else if (token[i] == '\'' && quote[0] == 0 && quote[1] == 1 && prev != '\\')
			quote[1] = 0;
		if (!(((token[i] == '\'' && quote[0] != 1) || (token[i] == '\"' && quote[1] != 1) || token[i] == '\\') && prev != '\\'))
			new[j++] = token[i];
		prev = token[i];
		i++;
	}
	new[j] = '\0';
	free(token);
	return (new);
}

// void	trim_quotes(char *token)
// {
// 	int	new_len;
// 	char *result;
// 	int i;
// 	int y;

// 	i = 0;
// 	y = 0;
// 	new_len = ft_strlen(token);
// 	if ((token[new_len-1] == '\"' || token[new_len-1] == '\'')
// 				&& (token[new_len-2] != '\\'))
// 		new_len--;
// 	if (token[0] == '\"' || token[0] == '\'')
// 		new_len--;
// 	result = malloc(sizeof(char) * (new_len + 1));
// 	if (token[i] == '\'' || token[i] == '\"')
// 		i++;
// 	while (token[i] && i < new_len)
// 	{

// 	}


// }

// void	trim_tokens(char **tokens)
// {
// 	int i;

// 	i = 0;
// 	while (tokens[i])
// 	{

// 	}
// }

void	shell_loop_2(t_info *info)
{
	char	**com;
	int		i;

	i = 0;
	while (1)
	{
		signal(SIGINT, INThandler);
		signal(SIGQUIT, quit_handler);
		write(1, "\U0001f921> ", 7);
		com = ft_get_command();
		check_var(com, info->our_env, info);
		while(com[i])
		{
			com[i] = ft_copy_without_quotes(com[i]);
			i++;
		}
		i = 0;
		if (com[0] != NULL)
			execute(com, -1, 1, info);
		if (com[0])
			free_split(com);
	}
}
