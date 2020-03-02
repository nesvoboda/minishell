/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:04:03 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/02 16:32:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tabcpy(char **dst, char **src)
{
	int i;

	i = 0;
	if (src == NULL)
		return ;
	while (src[i] != NULL)
	{
		dst[i] = ft_strdup(src[i]);
		free(src[i]);
		i++;
	}
	dst[i] = NULL;
}

char	**ft_tabdup(char **src)
{
	char	**dst;
	int		i;

	i = 0;
	if (!(dst = malloc(sizeof(char *) * (ft_tablen(src) + 1))))
		exit(1);
	if (src == NULL)
		return (NULL);
	while (src[i] != NULL)
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**tabjoin(char **tab1, char **tab2)
{
	char	**new;
	int		size;
	int		i;

	i = 0;
	size = ft_tablen(tab1);
	if (!(new = malloc(sizeof(char *) * (size + ft_tablen(tab2) + 1))))
		return (NULL);
	ft_tabcpy(new, tab1);
	while (tab2[i])
	{
		new[size + i] = ft_strdup(tab2[i]);
		i++;
	}
	new[size + i] = NULL;
	free(tab1);
	free_split(tab2);
	return (new);
}
