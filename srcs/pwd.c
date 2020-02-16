/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:38:08 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/16 18:32:43 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** pwd() returns current working path. getcwd() mallocs the return string if
** its first argument is NULL.
*/

int		print_pwd(int fd)
{
	int		len;
	char	*str;

	str = pwd();
	len = ft_strlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
	return (0);
}

char	*pwd(void)
{
	return (getcwd(NULL, 0));
}
