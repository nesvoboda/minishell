/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:16:18 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 18:21:31 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handler(char *tokens, char *err, int code)
{
	ft_puterr("our sh: ");
	ft_puterr(tokens);
	ft_puterr(": ");
	ft_puterr(err);
	ft_puterr("\n");
	if (code != -1)
		exit(code);
}
