/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:36:43 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 22:22:56 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_choose_path(char *paths, char *token)
{
	int		k;
	int		j;
	char	*str;

	j = 0;
	k = 0;
	if (!(str = malloc(sizeof(char) * ft_strlen(paths) +
		ft_strlen(token) + 2)))
		return (NULL);
	while (paths[j] != '\0')
	{
		str[j] = paths[j];
		j++;
	}
	if (j != 0 && paths[j - 1] != '/')
		str[j++] = '/';
	while (token[k])
	{
		str[j + k] = token[k];
		k++;
	}
	str[k + j] = '\0';
	return (str);
}

char	*ft_lolal_ex(char **token, struct stat *stats, char *program_name)
{
	mode_t bits;

	if (stat(token[0], stats) != 0)
		error_handler(token[0], "No such file or directory", 127, program_name);
	bits = stats->st_mode;
	if (S_ISDIR(stats->st_mode))
		error_handler(token[0], "is a directory", 126, program_name);
	if ((bits & S_IXUSR) == 0)
		error_handler(token[0], "Permission denied", 126, program_name);
	return (token[0]);
}

int		contain_path(char *token)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*path_helper(char *path, char *token, struct stat *stats,
															char *program_name)
{
	char *str;

	str = ft_choose_path(path, token);
	if (stat(str, stats) == 0)
		return (ft_lolal_ex(&str, stats, program_name));
	free(str);
	return (NULL);
}

char	*ft_exec_path(char **token, char **our_env, char *program_name)
{
	char			**paths;
	int				num_path;
	struct stat		stats;
	int				i;

	i = 0;
	num_path = ft_find_paths(our_env);
	if (contain_path(token[0]))
		return (ft_lolal_ex(token, &stats, program_name));
	if (num_path != -1)
	{
		if (!(paths = ft_split(&our_env[num_path][5], ':')))
			return (NULL);
		while (paths[i])
		{
			if (path_helper(paths[i], token[0], &stats, program_name))
				return (path_helper(paths[i], token[0], &stats, program_name));
			i++;
		}
	}
	else if (stat(token[0], &stats) == 0)
		return (ft_lolal_ex(token, &stats, program_name));
	return (NULL);
}
