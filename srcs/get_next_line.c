/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:16:35 by ablanar           #+#    #+#             */
/*   Updated: 2019/10/30 15:17:21 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char		*ft_store(t_line *list, int len)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	j = 0;
	while (list->line[i] != '\n' && list->line[i] != '\0')
		i++;
	if (!(tmp = malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	while (i + j + 1 < len)
	{
		tmp[j] = list->line[j + i + 1];
		j++;
	}
	tmp[j] = '\0';
	free(list->line);
	return (tmp);
}

int			ft_add_line(char **line, t_line *list)
{
	int i;
	int length;

	i = 0;
	while (list->line[i])
		i++;
	length = i;
	if (!(*line = malloc(sizeof(char) * (length + 1))))
		return (-1);
	i = 0;
	while (list->line[i] != '\n' && list->line[i] != '\0')
	{
		(*line)[i] = list->line[i];
		i++;
	}
	(*line)[i] = '\0';
	if (!(list->line = ft_store(list, length)))
		return (-1);
	return (1);
}

int			ft_read(int fd, t_line *list, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		res_read;

	while ((res_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (res_read < 0)
			return (-1);
		if (!(list->line = ft_strjoin(list->line, buf, res_read)))
			return (-1);
		if (ft_check(list->line) == 1)
		{
			ft_add_line(line, list);
			return (1);
		}
	}
	if (ft_check(list->line) != 0)
	{
		ft_add_line(line, list);
		return (1);
	}
	ft_add_line(line, list);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_node	*list = NULL;
	t_line			*cur;
	int				id;

	if (BUFFER_SIZE == 0 || line == NULL)
	{
		if (list)
			ft_clean(&list, list->line, fd);
		return (-1);
	}
	if (!(cur = ft_find_fd(fd, &list)))
	{
		ft_clean(&list, cur, fd);
		return (-1);
	}
	if (((id = ft_read(fd, cur, line)) == -1))
	{
		ft_clean(&list, cur, fd);
		return (-1);
	}
	else if (id == 1)
		return (1);
	else
		return (ft_clean(&list, cur, fd));
}
