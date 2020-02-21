/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:17:34 by ablanar           #+#    #+#             */
/*   Updated: 2019/10/30 15:18:41 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_check(char *s)
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

void			ft_del_node(t_line *cur, t_node **list)
{
	t_node *buf;

	free(cur->line);
	cur->line = NULL;
	free((*list)->line);
	(*list)->line = NULL;
	if ((*list)->next != NULL)
	{
		buf = *list;
		(*list) = (*list)->next;
		free(buf);
		buf = NULL;
	}
	else
	{
		free(*list);
		*list = NULL;
	}
}

int				ft_clean(t_node **list, t_line *cur, int fd)
{
	t_node *header;

	if (*list && cur)
	{
		header = *list;
		while (*list != NULL)
		{
			if ((*list)->fd == fd)
			{
				if (header == *list)
					header = (*list)->next;
				ft_del_node(cur, list);
				*list = header;
				return (0);
			}
			*list = (*list)->next;
		}
	}
	return (0);
}

int				ft_list_add_back(int fd, t_node **list, t_line *new)
{
	t_node *buf;

	if (*list)
	{
		buf = *list;
		while ((*list)->next != NULL)
			(*list) = (*list)->next;
		if (!((*list)->next = malloc(sizeof(t_node))))
			return (-1);
		(*list) = (*list)->next;
		(*list)->line = new;
		(*list)->fd = fd;
		(*list)->next = NULL;
		*list = buf;
	}
	else
	{
		if (!(*list = malloc(sizeof(t_node))))
			return (-1);
		(*list)->line = new;
		(*list)->fd = fd;
		(*list)->next = NULL;
	}
	return (1);
}

t_line			*ft_find_fd(int fd, t_node **list)
{
	t_node *buf;
	t_line *new;

	if (*list)
	{
		buf = *list;
		while (buf != NULL)
		{
			if (buf->fd == fd)
				return (buf->line);
			buf = buf->next;
		}
	}
	if (!(new = malloc(sizeof(t_line))))
		return (NULL);
	if (!(new->line = malloc(sizeof(char) + 1)))
		return (NULL);
	new->line[0] = '\0';
	new->next = NULL;
	if (!(ft_list_add_back(fd, list, new)))
		return (NULL);
	return (new);
}
