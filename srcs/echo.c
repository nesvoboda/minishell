/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:28:49 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/12 15:19:42 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// Remove before flight
#include <string.h>


int	ft_echo(char **tokens, int fd)
{
	int k;
	int flag;

	k = 1;
	flag = 0;
	if (tokens[k] != NULL && !strcmp(tokens[k], "-n")) //change strcmp
	{
		k = 2;
		flag = 1;
	}
	while (tokens[k] != NULL && !is_special(tokens[k]))
	{
		if ((k > 1 && flag == 0) || (k > 2 && flag == 1))
			write(fd, " ", 1);
		write(fd, tokens[k], ft_strlen(tokens[k]));

		k++;
	}
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
