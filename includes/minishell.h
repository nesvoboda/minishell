/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:55 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/11 17:12:54 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include <fcntl.h>
int g_fd;
int		ft_strlen(char *str);
char	**tokenize(int fd, int *ret);
char	*pwd(void);
char	**ft_split(char const *s, char c);
void	shell_loop(int fd);
void	ft_putstr(char *str);
void	ft_echo(char **tokens, int fd);
int		ft_exec(char **tokens, int fd, int output, char **our_env);
void	init_env(char ***our_env, char **environ);
int		find_env(char **our_env, char *key);
void	remove_env(char ***our_env, char *key);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		envsize(char **our_env);
void	add_env(char ***our_env, char *entry);
void	print_env(char **our_env);
int 	ft_cd(char **tokens);
void	ft_exit(char **token);
void	free_split(char **splitted);
void	print_env(char **our_env);
int		envsize(char **our_env);
void	add_env(char ***our_env, char *entry);
void	init_env(char ***our_env, char **environ);
int		find_env(char **our_env, char *key);

int		redir(char *filename);
int		rredir(char *filename);

void	shell_loop_2();
void	switchboard(char **tokens, int fd, int output, char ***our_env);
void	execute(char **tokens, int fd, int output, char ***our_env);
char	**ft_get_command();
int		is_special(char *token);
int		next_special(char **tokens);
void	print_pwd(int fd);

int		is(char *token, char *query);
int		is_special(char *token);
int		next_special(char **tokens);
void	add_all_env(char ***our_env, char **tokens);
int		ft_tablen(char **tab);
int		find_equals(char *str);
int		remove_all_env(char ***our_env, char **tokens);
int		check_key(char *str);
void	ft_puterr(char *str);
void	INThandler(int sig);
char	*ft_strdup(char *s1);

/*
** Deprecated
*/
void	check_var(char **tokens, char **our_env);
char	*r_to_file(char *filename, char *content);
char	*rr_to_file(char *filename, char *content);

#endif
