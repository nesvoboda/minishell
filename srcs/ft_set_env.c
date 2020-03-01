/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:21:35 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 18:52:12 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_set_env(char *key, char **our_env, t_info info)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = ft_strdup(key);
	while (cpy[i] != '\0' && cpy[i] != ' ' && cpy[i] != '\"' &&
			cpy[i] != '$' && cpy[i] != '?')
		i++;
	cpy[i] = '\0';
	i = 0;
	if (key[0] == '?')
	{
		free(cpy);
		return (stringify_status(info.status));
	}
	while (our_env[i] && ft_strlen(cpy) != 0)
	{
		if (!ft_strncmp(our_env[i++], cpy, find_equals(cpy)))
		{
			free(cpy);
			return (our_env[--i]);
		}
	}
	free(cpy);
	return (NULL);
}
