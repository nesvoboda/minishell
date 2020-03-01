/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:16:18 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 13:39:57 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handler(char *tokens, char *err, int code, char *program_name)
{
	ft_puterr(program_name);
	ft_puterr(": ");
	ft_puterr(tokens);
	ft_puterr(": ");
	ft_puterr(err);
	ft_puterr("\n");
	if (code != -1)
		exit(code);
}
