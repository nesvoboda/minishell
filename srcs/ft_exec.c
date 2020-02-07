/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:57:10 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/07 18:02:18 by ashishae         ###   ########.fr       */
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

	pid = fork();
	if (fd != -1)
	{
		saved_stdin = dup(0);
		dup2(fd, 0);
	}
	if (output != 1)
	{
		saved_stdout = dup(1);
		dup2(output, 1);
		dup2(output, 2);
	}
	arguments = get_arguments(tokens);
	if (pid == 0)
	{
		close(fd);
		if (execve(tokens[0], arguments, arguments) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
		}
		printf("HUI");
		close(fd);
		close(output);
		exit(EXIT_FAILURE);
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
	}
	if (output != 1)
	{
		dup2(saved_stdout, 1);
	}
	if (fd != -1)
	{
		dup2(saved_stdin, 0);
	}
	return (1);
}