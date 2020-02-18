/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:07:53 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/18 15:42:53 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	extern char	**environ;
	t_info		info;

	(void)ac;
	(void)av;
	g_flag = 1;
	init_env(&(info.our_env), environ);
	shell_loop_2(&info);
	return (0);
}
