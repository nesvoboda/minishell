/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_norm_ft_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:43:29 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/02 20:16:40 by ashishae         ###   ########.fr       */
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

int		run(char **tokens, t_info *info, char **arguments)
{
	pid_t	pid;
	int		status;
	char	*com;

	com = NULL;
	pid = info->is_forked ? 0 : fork();
	status = 0;
	if (pid == 0)
	{
		if (!(com = ft_exec_path(tokens, info->our_env, info->program_name)) ||
			(execve(com, arguments, info->our_env)) == -1)
			ft_run_helper(tokens[0], info->program_name, errno);
		exit(0);
	}
	else if (pid < 0)
		error_handler(tokens[0], "fork error", 127, info->program_name);
	else
	{
		status = ft_wait_com(pid, status);
		free(com);
	}
	return (g_kek == 0 ? *g_status : status);
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
	ret = run(tokens, info, arguments);
	free_split(arguments);
	reset_stream_redirects(fd, output, saved_stdout, saved_stdin);
	if (saved_stdout != 1)
		close(saved_stdout);
	if (saved_stdin != 0)
		close(saved_stdin);
	return (ret);
}
