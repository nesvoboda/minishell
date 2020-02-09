/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:57:10 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/09 15:23:07 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

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

int ft_find_paths(char **our_env)
{
	int i;

	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_exec_path(char **token, char **our_env)
{
	char	**paths;
	int		num_path;
	int		i;
	char *str;
	int j;
	int k;
 	struct stat stats;

	i = 0;
	num_path = ft_find_paths(our_env);
	paths = ft_split(&our_env[num_path][5], ':');
	while (paths[i])
	{
		j = 0;
		k = 0;
		str = malloc(sizeof(char) * ft_strlen(paths[i]) + ft_strlen(token[0]) + 2);
		while (paths[i][j] != '\0')
		{
			str[j] = paths[i][j];
			j++;
		}
		str[j] = '/';
		while (token[0][k])
		{
			str[j + 1 + k] = token[0][k];
			k++;
		}
		str[k+j + 1] = '\0';
		if (stat(str, &stats) == 0)
			return (str);
		i++;
		free(str);
	}
	return (NULL);
}

int	ft_exec(char **tokens, int fd, int output, char **our_env)
{
	pid_t	pid;
	int		status;
	char	**arguments;
	char	*com = NULL;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	arguments = get_arguments(tokens);
	pid = fork();
	status = 0;

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

	if (pid == 0)
	{
		if (!(com = ft_exec_path(tokens, our_env)) || execve(com, arguments, our_env) == -1)
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
		free(com);

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
	free (arguments);
	return (status);
}
