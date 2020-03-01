/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:14:07 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 17:14:29 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_strjoin(char *s1, char *s2, int res)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(tmp = malloc(sizeof(char) * (i + res + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (j < res)
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[j + i] = '\0';
	free(s1);
	return (tmp);
}
