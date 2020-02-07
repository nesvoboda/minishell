/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:18:17 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 20:05:57 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** Deprecated. Stays until we remake tests.
*/
#include <string.h>

char	*r_to_file(char *filename, char *content)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	write(fd, content, ft_strlen(content));
	close(fd);
	return (strdup(""));
}

/*
** Deprecated. Stays until we remake tests.
*/

char	*rr_to_file(char *filename, char *content)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	write(fd, content, ft_strlen(content));
	close(fd);
	return (strdup(""));
}

int	redir(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	return (fd);
}

int	rredir(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	return (fd);
}