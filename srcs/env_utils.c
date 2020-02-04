/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:42:22 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/04 19:20:17 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** print_env() prints out a null-terminated string array, each string on its
** own line.
*/

void	print_env(char **our_env)
{
	int	i;

	i = 0;
	while (our_env[i])
	{
		ft_putstr(our_env[i++]);
		write(1, "\n", 1);
	}
}