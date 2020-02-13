/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/13 17:43:39 by ashishae         ###   ########.fr       */
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

void	shell_loop_2(t_info *info)
{
	char **com;

	while (1)
	{
		signal(SIGINT, INThandler);
		signal(SIGQUIT, quit_handler);
		write(1, "> ", 2);
		com = ft_get_command();
		check_var(com, info->our_env, info);

		if (com[0] != NULL)
			execute(com, -1, 1, info);
		if (com[0])
			free_split(com);
	}
}
