/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:07:53 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/02 16:34:15 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** exec_name() tries to shave off ./ from av[0] to get the executable name.
** It is protected from premature string termination.
*/

char	*exec_name(char *av0)
{
	int i;

	i = 0;
	while (av0[i] && i < 2)
		i++;
	return (&av0[i]);
}

int		main(int ac, char **av)
{
	extern char	**environ;
	t_info		info;
	mode_t		bits;
	struct stat	stats;

	fstat(1, &stats);
	(void)ac;
	bits = stats.st_mode;
	g_flag = 1;
	g_line = NULL;
	g_status = &(info.status);
	info.is_forked = 0;
	info.program_name = exec_name(av[0]);
	init_env(&(info.our_env), environ);
	shell_loop_2(&info);
	return (0);
}
