/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:55 by ashishae          #+#    #+#             */
/*   Updated: 2020/02/12 15:38:09 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>

# include <fcntl.h>

typedef struct	s_info
{
	int	status;
	char **our_env;
}				t_info;

int				g_fd;
int				ft_strlen(char *str);
char			**tokenize(int fd, int *ret);
char			*pwd(void);
char			**ft_split(char const *s, char c);
void			shell_loop(int fd);
void			ft_putstr(char *str);
int				ft_echo(char **tokens, int fd);
int				ft_exec(char **tokens, int fd, int output, char **our_env);
void			init_env(char ***our_env, char **environ);
int				find_env(char **our_env, char *key);
void			remove_env(char ***our_env, char *key);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				envsize(char **our_env);
void			add_env(char ***our_env, char *entry);
void			print_env(char **our_env);
int 			ft_cd(char **tokens);
void			ft_exit(char **token, int status);
void			free_split(char **splitted);
void			print_env(char **our_env);
int				envsize(char **our_env);
void			add_env(char ***our_env, char *entry);
void			init_env(char ***our_env, char **environ);
int				find_env(char **our_env, char *key);

int				redir(char *filename, int *status);
int				rredir(char *filename, int *status);

void			shell_loop_2(t_info *info);
void			switchboard(char **tokens, int fd, int output, t_info *info);
void			execute(char **tokens, int fd, int output, t_info *info);
char			**ft_get_command();
int				is_special(char *token);
int				next_special(char **tokens);
int				print_pwd(int fd);

int				is(char *token, char *query);
int				is_special(char *token);
int				next_special(char **tokens);
int				add_all_env(char ***our_env, char **tokens);
int				ft_tablen(char **tab);
int				find_equals(char *str);
int				remove_all_env(char ***our_env, char **tokens);
int				check_key(char *str);
void			ft_puterr(char *str);
void			INThandler(int sig);
char			*ft_strdup(char *s1);
void			check_var(char **tokens, char **our_env);
int				left_redir(char *filename, int *status);
void			ft_tabcpy(char **dst, char **src);
char			*ft_add_char(char **line, char c);
void			ft_start_input(char **input, char *prev, char ***tokens, int *q);

#endif
