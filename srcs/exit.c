/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:02:34 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/12 15:22:47 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exit(char **tokens, int status)
{
	(void)tokens;
//	free_split(tokens);
	write(1, "exit\n", 5);
	exit(status);
}
