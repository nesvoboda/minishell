/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:18 by ablanar           #+#    #+#             */
/*   Updated: 2019/10/30 15:18:32 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_line
{
	char			*line;
	struct s_line	*next;
}					t_line;

typedef struct		s_node
{
	int				fd;
	t_line			*line;
	struct s_node	*next;
}					t_node;
int					get_next_line(int fd, char **line);
t_line				*ft_find_fd(int fd, t_node **list);
int					ft_clean(t_node **list, t_line *cur, int fd);
int					ft_check(char *s);
#endif
