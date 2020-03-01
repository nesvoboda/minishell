/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:31:09 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 13:06:26 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	get_home() tries to find $HOME in the environment and returns its value.
**	If it fails to do so, it returns NULL.
*/

void	cd_error(int err, char *filename, char *program_name)
{
	ft_puterr(program_name);
	ft_puterr(": cd: ");
	ft_puterr(filename);
	ft_puterr(": ");
	ft_puterr(strerror(err));
	ft_puterr("\n");
}

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

int		ft_cd(char **tokens, char **our_env, char *program_name)
{
	char	*home;
	int		ret;

	if (tokens[1])
		tokens[1] = ft_copy_without_quotes(tokens[1]);
	if ((next_special(tokens) == 1) ||
			(next_special(tokens) == -1 && tokens[1] == NULL))
	{
		if ((home = get_home(our_env)))
			ret = chdir(home);
		else
		{
			ft_puterr(program_name);
			ft_puterr(": cd: HOME not set\n");
			return (1);
		}
	}
	else
		ret = chdir(tokens[1]);
	if (ret == -1)
	{
		cd_error(errno, tokens[1], program_name);
		return (1);
	}
	return (0);
}
