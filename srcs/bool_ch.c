/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_ch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:09:58 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 18:10:39 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		error_bool(char *token_sp, char *token_sp1)
{
	if (((token_sp1 == NULL) || is_special(token_sp1)
			== 1) && !is(token_sp, "|") && (!is(token_sp, ";")
			|| (token_sp1 != NULL && is_special(token_sp1))))
		return (1);
	return (0);
}

int		error_bool2(char *token_sp, char *token_sp1)
{
	if (is(token_sp, ";") && token_sp1 != NULL && is(token_sp1, ";"))
		return (1);
	return (0);
}

int		redir_bool(char *token_sp)
{
	if (is(token_sp, ">") || is(token_sp, ">>")
		|| is(token_sp, "<"))
		return (1);
	return (0);
}
