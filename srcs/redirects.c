/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:18:17 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 13:02:22 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(int err, char *filename, char *program_name)
{
	ft_puterr(program_name);
	ft_puterr(": ");
	ft_puterr(filename);
	ft_puterr(": ");
	ft_puterr(strerror(err));
	ft_puterr("\n");
}

int		redir(char *filename, int *status, char *program_name)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | 
														S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename, program_name);
	}
	return (fd);
}

int		rredir(char *filename, int *status, char *program_name)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
														S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename, program_name);
	}
	return (fd);
}

int		left_redir(char *filename, int *status, char *program_name)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename, program_name);
	}
	return (fd);
}
