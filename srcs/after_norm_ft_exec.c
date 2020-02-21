/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_norm_ft_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:43:29 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/21 15:56:19 by ablanar          ###   ########.fr       */
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
	waitpid(pid, &status, 0);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
	{
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int		run(char **tokens, char **our_env, char **arguments, int is_forked)
{
	pid_t	pid;
	int		status;
	char	*com;

	com = NULL;
	if (!is_forked)
		pid = fork();
	else
		pid = 0;
	status = 0;
	if (pid == 0)
	{
		if (!(com = ft_exec_path(tokens, our_env)) ||
			execve(com, arguments, our_env) == -1)
		{
			ft_puterr("our sh: ");
			ft_puterr(tokens[0]);
			ft_puterr(": ");
			ft_puterr(strerror(errno));
			ft_puterr("\n");
			exit(errno);
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

int		ft_exec(char **tokens, int fd, int output, t_info *info)
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
	ret = run(tokens, info->our_env, arguments, info->is_forked);
	free(arguments);
	reset_stream_redirects(fd, output, saved_stdout, saved_stdin);
	return (ret);
}
