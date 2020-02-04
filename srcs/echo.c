/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:28:49 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/04 14:15:07 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// Remove before flight
#include <string.h>


void ft_echo(char **tokens)
{
	int k;
	int flag;

	k = 1;
	flag = 0;
	if (tokens[k] != NULL && !strcmp(tokens[k], "-n")) //change compare
	{
		k = 2;
		flag = 1;
	}
	while (tokens[k] != NULL)
	{
		if ((k > 1 && flag == 0) || (k > 2 && flag == 1))
			write(1, " ", 1);
		write(1, tokens[k], ft_strlen(tokens[k]));

		k++;
	}
	if (!flag)
		write(1, "\n", 1);
}
