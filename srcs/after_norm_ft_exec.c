/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_norm_ft_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:43:29 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/18 21:17:32 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	enable_stream_redirects(int fd, int output)
{
	if (output != 1)
	{
		close(STDOUT_FILENO);
		dup(output);
		close(output);
	}
	if (fd != -1)
	{
		close(STDIN_FILENO);
		dup(fd);
		close(fd);
	}
}

void	reset_stream_redirects(int fd, int output, int saved_stdout,
								int saved_stdin)
{
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

int		ft_wait_com(int pid, int status)
{
	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
	{
		write(1, "1", 1);
		waitpid(pid, &status, WUNTRACED);
	}
	return (status);
}

int		run(char **tokens, char **our_env, char **arguments)
{
	pid_t	pid;
	int		status;
	char	*com;

	com = NULL;
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (!(com = ft_exec_path(tokens, our_env)) ||
			execve(com, arguments, our_env) == -1)
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
		status = ft_wait_com(pid, status);
		free(com);
	}
	return (status);
}

int		ft_exec(char **tokens, int fd, int output, char **our_env)
{
	int		saved_stdout;
	int		saved_stdin;
	int		ret;
	char	**arguments;

	saved_stdin = 0;
	saved_stdout = 1;
	if (fd != -1)
		saved_stdin = dup(0);
	if (output != 1)
		saved_stdout = dup(1);
	enable_stream_redirects(fd, output);
	arguments = get_arguments(tokens);
	g_flag = 0;
	ret = run(tokens, our_env, arguments);
	free(arguments);
	reset_stream_redirects(fd, output, saved_stdout, saved_stdin);
	return (ret);
}
