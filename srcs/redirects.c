/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:18:17 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/07 15:06:06 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	r_to_file(char *filename, char *content)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	write(fd, content, ft_strlen(content));
	close(fd);
}

void	rr_to_file(char *filename, char *content)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	write(fd, content, ft_strlen(content));
	close(fd);
}