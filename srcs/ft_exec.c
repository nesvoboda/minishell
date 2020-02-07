/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:57:10 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/07 18:51:20 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>

int tokens_len(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

char **get_arguments(char **tokens)
{
	char	**result;
	int		length;
	int		i;

	length = next_special(tokens);
	if (length == -1)
		length = tokens_len(tokens);
	if (!(result = malloc(sizeof(char *) * (length + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < length)
	{
		result[i] = tokens[i];
		i++;
	}
	result[i] = NULL;
	return (result);
}

#include <stdio.h>

int	ft_exec(char **tokens, int fd, int output)
{
	pid_t	pid;
	int		status;
	char	**arguments;

	int		saved_stdout;
	int		saved_stdin;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	pid = fork();


	/* this is the ls */
	if (output != 1)
	{
		//close(fd);           /* close read pipe */
		close(STDOUT_FILENO);   /* close standard out */
		dup(output);             /* make write pipe stand ard out */
		close(output);           /* close my ptr to write pipe */
	}
	if (fd != -1)
	{
		            /* this is the cat */
		//close(output);           /* close write pipe */
		close(STDIN_FILENO);    /* close standard in */
		dup(fd);             /* make read pipe standard in */
		close(fd);           /* close my ptr to read pipe */
	}
	
	arguments = get_arguments(tokens);
	if (pid == 0)
	{

		printf("Running |%s| to %d\n", tokens[0], fd);
		if (execve(tokens[0], arguments, 0) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
		}
		exit(0);
	}
	else if (pid < 0)
		write(2, "Errror in forkin\n", ft_strlen("Errror in forkin\n"));
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			write(1, "1", 1);
			waitpid(pid, &status, WUNTRACED);
		}
		if (output != 1)
		{
			close(STDOUT_FILENO);
			dup(saved_stdout);
		}
		if (fd != -1)
		{
			close(STDIN_FILENO);
			dup(saved_stdin);
		}
	}

	return (1);
}