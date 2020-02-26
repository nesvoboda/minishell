/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:18:17 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/26 13:13:08 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(int err, char *filename)
{
	ft_puterr("our shell: ");
	ft_puterr(filename);
	ft_puterr(": ");
	ft_puterr(strerror(err));
	ft_puterr("\n");
}

int		redir(char *filename, int *status)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | 
														S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename);
	}
	return (fd);
}

int		rredir(char *filename, int *status)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | 
														S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename);
	}
	return (fd);
}

int		left_redir(char *filename, int *status)
{
	int			fd;
	extern int	errno;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		*status = 1;
		handle_error(errno, filename);
	}
	return (fd);
}
