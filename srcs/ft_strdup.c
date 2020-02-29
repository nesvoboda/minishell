/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:28:42 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/16 17:28:55 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s1);
	if ((p = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strlcpy(p, s1, len + 1);
	p[len] = '\0';
	return (p);
}

int		is_alnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}