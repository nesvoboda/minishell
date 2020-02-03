/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:38:08 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/03 13:45:41 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** pwd() returns current working path. getcwd() mallocs the return string if
** its first argument is NULL.
*/

char *pwd(void)
{
	return (getcwd(NULL, 0));
}