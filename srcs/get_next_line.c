/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:16:35 by ablanar           #+#    #+#             */
/*   Updated: 2020/02/26 19:12:02 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "get_next_line.h"

char *g_line;
char		*ft_strjoin(char *s1, char *s2, int res)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(tmp = malloc(sizeof(char) * (i + res + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (j < res)
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[j + i] = '\0';
	free(s1);
	return (tmp);
}

char		*ft_store(char *new, int len)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	j = 0;
	while (new[i] != '\n' && new[i] != '\0')
		i++;
	if (!(tmp = malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	while (i + j + 1 < len)
	{
		tmp[j] = new[j + i + 1];
		j++;
	}
	tmp[j] = '\0';
	free(new);
	return (tmp);
}

int			ft_add_line(char **line)
{
	int i;
	int length;

	i = 0;
	while (g_line[i])
		i++;
	length = i;
	if (!(*line = malloc(sizeof(char) * (length + 1))))
		return (-1);
	i = 0;
	while (g_line[i] != '\n' && g_line[i] != '\0')
	{
		(*line)[i] = g_line[i];
		i++;
	}
	(*line)[i] = '\0';
	if (!(g_line = ft_store(g_line, length)))
		return (-1);
	return (1);
}

int			ft_read(int fd, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		res_read;

	while (((res_read = read(fd, buf, BUFFER_SIZE)) || g_line[0]))
	{
		if (res_read == 0)
			write(1, "  \b\b", 4);
		if (res_read < 0)
			return (-1);
		if (!(g_line = ft_strjoin(g_line, buf, res_read)))
			return (-1);
		if (ft_check(g_line) == 1)
		{
			ft_add_line(line);
			return (1);
		}
	}
	if (ft_check(g_line) != 0)
	{
		ft_add_line(line);
		return (1);
	}
	ft_add_line(line);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int id;

	g_line = malloc(sizeof(char) * 1);
	g_line[0] = '\0';
	if (BUFFER_SIZE == 0 || line == NULL)
		return (-1);
	if (((id = ft_read(fd, line)) == -1))
	{
		free(g_line);
		return (-1);
	}
	else if (id == 1)
	{
		free(g_line);
		return (1);
	}
	else
		return (0);
}
