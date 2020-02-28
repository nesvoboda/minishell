/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:36:43 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/28 18:37:10 by ablanar          ###   ########.fr       */
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
	str[j] = '/';
	while (token[k])
	{
		str[j + 1 + k] = token[k];
		k++;
	}
	str[k + j + 1] = '\0';
	return (str);
}

char	*ft_lolal_ex(char **token, struct stat *stats)
{
	mode_t bits;

	if (stat(token[0], stats) != 0)
		error_handler(token[0], "No such file or directory", 127);
	bits = stats->st_mode;
	if ((bits & S_IXUSR) == 0)
		error_handler(token[0], "Permission denied", 126);
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

char	*path_helper(char *path, char *token, struct stat *stats)
{
	char *str;

	str = ft_choose_path(path, token);
	if (stat(str, stats) == 0)
		return (ft_lolal_ex(&str, stats));
	free(str);
	return (NULL);
}

char	*ft_exec_path(char **token, char **our_env)
{
	char			**paths;
	int				num_path;
	struct stat		stats;
	int				i;

	i = 0;
	num_path = ft_find_paths(our_env);
	if (contain_path(token[0]))
		return (ft_lolal_ex(token, &stats));
	if (num_path != -1)
	{
		if (!(paths = ft_split(&our_env[num_path][5], ':')))
			return (NULL);
		while (paths[i])
		{
			if (path_helper(paths[i], token[0], &stats))
				return (path_helper(paths[i], token[0], &stats));
			i++;
		}
	}
	else if (stat(token[0], &stats) == 0)
		return (ft_lolal_ex(token, &stats));
	return (NULL);
}
