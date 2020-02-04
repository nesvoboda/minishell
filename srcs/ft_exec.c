/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:57:10 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/04 17:46:26 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include <string.h>
#include <sys/errno.h>

int ft_exec(char **tokens)
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(tokens[0], tokens, tokens) == -1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "!\n", 2);
		}
		exit(EXIT_FAILURE);
	}
		else if (pid < 0)
		{
			write(2, "Errror in forkin\n", ft_strlen("Errror in forkin\n"));
		}
		else {
	    do {
	      wpid = waitpid(pid, &status, WUNTRACED);
	    }
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	  }

	  return 1;
}
