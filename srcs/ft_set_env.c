/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:21:35 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/02 18:02:45 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_keychar(char c)
{
	return (c != '\0' && c != ' ' && c != '\"' && c != '$' && c != '?');
}

char	*ft_set_env(char *key, char **our_env, t_info info)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = ft_strdup(key);
	while (is_keychar(cpy[i]))
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
		if (!ft_strncmp(our_env[i], cpy, find_equals(our_env[i])))
		{
			free(cpy);
			return (our_env[i]);
		}
		i++;
	}
	free(cpy);
	return (NULL);
}
