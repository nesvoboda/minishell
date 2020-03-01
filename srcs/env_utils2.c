/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:03:01 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/01 16:03:09 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		proper_key(char *key)
{
	int i;
	int stop;
	int equals_found;
	int	equals;

	equals = find_equals(key);
	if (equals == 0)
		return (0);
	equals_found = equals < ft_strlen(key);
	i = 0;
	stop = equals_found ? equals - 1 : ft_strlen(key);
	while (i < stop)
	{
		if (!is_alnum(key[i]))
			return (0);
		i++;
	}
	if (equals_found && !is_alnum(key[i]) && key[i] != '+')
		return (0);
	return (1);
}
