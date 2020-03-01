/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:28:41 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 18:28:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_check_dol(char **token, char ***nach, int n)
{
	char **new;

	if (token[0][0] == '\'' || token[0][0] == '\"')
		return ;
	new = ft_split(token[0], ' ');
	if (ft_tablen(new) > 1)
		ft_rearr(nach, new, n);
	else
		free_split(new);
}

void		ft_check_token(char ***tokens, char **our_env, t_info *info, int n)
{
	char	prev;
	int		q;
	int		i;

	i = 0;
	q = 0;
	prev = '\0';
	while (tokens[0][n][i])
	{
		if (tokens[0][n][i] == '\'' && q == 0 && prev != '\\')
			q = 1;
		else if (tokens[0][n][i] == '\'' && q == 1 && prev != '\\')
			q = 0;
		if (tokens[0][n][i] == '$' && prev != '\\' && q == 0)
		{
			replace_var(&tokens[0][n], our_env, info, i);
			ft_check_dol(&tokens[0][n], tokens, n);
			prev = '\0';
			i = 0;
		}
		else if (tokens[0][n][0])
			prev = tokens[0][n][i++];
	}
}

void		check_var(char ***tokens, char **our_env, t_info *info)
{
	int i;

	i = 0;
	while (tokens[0][i] && !is(tokens[0][i], ";"))
	{
		ft_check_token(tokens, our_env, info, i);
		i++;
	}
}
