/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:31:09 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/16 17:39:12 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	get_home() tries to find $HOME in the environment and returns its value.
**	If it fails to do so, it returns NULL.
*/

char	*get_home(char **our_env)
{
	int	home_key;
	int	home_position;

	home_key = find_env(our_env, "HOME");
	if (home_key < 0)
	{
		return (NULL);
	}
	home_position = find_equals(our_env[home_key]);
	return (our_env[home_key] + home_position + 1);
}

int		ft_cd(char **tokens, char **our_env)
{
	char	*home;
	int		ret;

	if ((next_special(tokens) == 1) ||
			(next_special(tokens) == -1 && tokens[1] == NULL))
	{
		if ((home = get_home(our_env)))
			ret = chdir(home);
		else
		{
			ft_puterr("our shell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		ret = chdir(tokens[1]);
	if (ret == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}
