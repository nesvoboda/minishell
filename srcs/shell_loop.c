/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:45 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/09 21:03:19 by ablanar          ###   ########.fr       */
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

/*
** tokenize() reads a line from a given fd and splits it into tokens.
*/

// char	**tokenize(int fd, int *ret)
// {
// 	char	*line;
// 	char	**tokens;

// 	*ret = get_next_line(fd, &line);
// 	if (*ret >= 0)
// 	{
// 		tokens = ft_split(line, ' ');
// 		free(line);
// 	}
// 	else
// 		return (0);

// 	return (tokens);
// }

// void	shell_loop(int fd)
// {
// 	char	**tokens;
// 	int		ret;

// 	ret = 1;
// 	while (ret > 0)
// 	{
// 		ft_putstr("> ");
// 		tokens = tokenize(fd, &ret);
// 		// // Diagnostic output
// 		// for (int i = 0; tokens[i] != 0; i++)
// 		// {
// 		// 	// printf("Token #%d is |%s|\n", i, tokens[i]);
// 		// }
// 		if (tokens && tokens[0])
// 		{
// 			if (!strcmp(tokens[0], "echo"))
// 				ft_echo(&tokens[0], 1);
// 			else if (!strcmp(tokens[0], "pwd"))
// 			{
// 				write(1, pwd(), ft_strlen(pwd()));
// 				write(1, "\n", 1);
// 			}
// 			else if (!strcmp(tokens[0], "cd"))
// 				ft_cd(tokens);
// 			else if (!strcmp(tokens[0], "exit"))
// 				ft_exit(tokens);
// 			else
// 				ft_exec(tokens, -1, 1);
// 			free_split(tokens);
// 		}

// 	}
// }

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




void	shell_loop_2(char ***our_env)
{
	char **com;
	int i;
	printf("Entered shell_loop_2\n");
	i = 0;
	while (1)
	{
		signal(SIGINT, INThandler);
		printf("Entered while loop\n");
		write(1, "> ", 2);
		com = ft_get_command();
		check_var(com, *our_env);
		// Diangostic output
		// printf("kek\n");
		while (com[i] != NULL)
		{
			printf("token%d %s\n",i, com[i]);
			i++;
		}
		i = 0;
		if (com[0] != NULL)
			execute(com, -1, 1, our_env);
		if (com[0])
			free_split(com);
	}
}
