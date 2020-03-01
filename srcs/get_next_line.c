/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:16:35 by ablanar           #+#    #+#             */
/*   Updated: 2020/03/01 13:28:34 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_check(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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

	while ((((res_read = read(fd, buf, BUFFER_SIZE)) || g_line[0])))
	{
		if (res_read == 0)
			write(1, "  \b\b", 4);
		else if (res_read < 0)
			return (-1);
		else if (!(g_line = ft_strjoin(g_line, buf, res_read)))
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

	g_kek = 1;
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
	{
		free(g_line);
		return (0);
	}
}
