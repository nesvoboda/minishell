/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:55 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/04 18:38:20 by ablanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

char	**tokenize(int fd, int *ret);
char	*pwd(void);
char	**ft_split(char const *s, char c);
void	shell_loop(void);
void	ft_putstr(char *str);
void	ft_echo(char **tokens);
int		ft_exec(char **tokens);
void	init_env(char ***our_env, char **environ);
int		find_env(char **our_env, char *key);
void	remove_env(char ***our_env, char *key);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_cd(char **tokens);
#endif
