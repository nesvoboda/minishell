/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:10:55 by ashishae          #+#    #+#             */
/*   Updated: 2020/03/02 20:50:19 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <signal.h>

int				g_flag;
int				g_kek;
int				*g_status;
char			*g_line;
char			*g_name;
typedef struct	s_info
{
	int		status;
	char	**our_env;
	int		last_char;
	int		is_forked;
	char	*program_name;
	int		pipe_in;
	int		pipe_out;
}				t_info;

char			*pwd(void);
char			**ft_split(char const *s, char c);
void			shell_loop(int fd);
void			ft_putstr(char *str);
int				ft_echo(char **tokens, int fd);
int				ft_exec(char **tokens, int fd, int output, t_info *info);
void			init_env(char ***our_env, char **environ);
int				find_env(char **our_env, char *key);
void			remove_env(char ***our_env, char *key);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				envsize(char **our_env);
void			add_env(char ***our_env, char *entry);
int				ft_cd(char **tokens, char **our_env, char *program_name);
void			ft_exit(char **token, int status, t_info *info);
void			free_split(char **splitted);
void			print_env(char **our_env);
int				envsize(char **our_env);
void			add_env(char ***our_env, char *entry);
void			init_env(char ***our_env, char **environ);
int				find_env(char **our_env, char *key);
char			*ft_copy_without_quotes(char *token);
int				redir(char *filename, int *status, char *program_name);
int				rredir(char *filename, int *status, char *program_name);
void			shell_loop_2(t_info *info);
void			switchboard(char **tokens, int fd, int output, t_info *info);
void			execute(char **tokens, int fd, int output, t_info *info);
char			**ft_get_command(t_info *info);
int				is_special(char *token);
int				next_special(char **tokens);
int				print_pwd(int fd);
int				is(char *token, char *query);
int				is_special(char *token);
int				next_special(char **tokens);
int				add_all_env(char ***our_env, char **tokens, int output,
															char *program_name);
int				ft_tablen(char **tab);
int				find_equals(char *str);
int				remove_all_env(char ***our_env, char **tokens,
															char *program_name);
int				check_key(char *str);
void			ft_puterr(char *str);
char			*ft_strdup(char *s1);
void			check_var(char ***tokens, char **our_env, t_info *info);
int				left_redir(char *filename, int *status, char *program_name);
void			ft_tabcpy(char **dst, char **src);
char			*ft_add_char(char **line, char c);
char			*ft_set_env(char *key, char **our_env, t_info info);
char			*stringify_status(int status);
char			**get_arguments(char **tokens);
char			*ft_exec_path(char **token, char **our_env, char *program_name);
void			handle_pipe(char **tokens, int fd, int output, t_info *info);
int				handle_left_redir(char **tokens, int output, t_info *info);
int				handle_right_redir(char **tokens, int fd, t_info *info);
int				handle_right_rredir(char **tokens, int fd, int special,
						t_info *info);
void			handle_redirects(char **tokens, int fd, int output,
									t_info *info);
int				is_spec(char *token);
int				next_spec(char **tokens);
void			vpered(char **com, int fd, int output, t_info *info);
void			recursive_madness(char **tokens, int io[2], t_info *info,
									char **token_nachalo);
int				ft_wait_com(int pid, int status);
int				get_next_line(int fd, char **line);
void			ft_start_input(char **input, int *i, char ***tokens, int *q);
int				next_redir(char **tokens);
void			syntax_error(char *error, int *status, t_info *info);
char			*ft_strjoin(char *s1, char *s2, int res);
void			concat_env(char ***our_env, char *entry);
void			handle_error(int err, char *filename, char *program_name);
void			env_noarg(char **our_env, int output);
void			ft_putstr_fd(char *str, int fd);
char			**ft_analyser(char *line, char **tokens, t_info *info);
char			*ft_itoa(int n);
void			error_handler(char *tokens, char *err, int code,
								char *program_name);
void			set_quotes(char *line, int *q, int i);
void			ft_rearr(char ***nach, char **new, int n);
void			replace_var(char **tokens, char **our_env, t_info *info, int i);
void			add_env_helper(char ***our_env, char **tokens, int *status,
															char *program_name);
void			invalid_identifier(char *token, char *command, int *status,
															char *program_name);
int				ft_atoi(const char *str);
void			init_env(char ***our_env, char **environ);
void			env_noarg(char **our_env, int output);
void			remove_env(char ***our_env, char *key);
char			*new_shlvl(char *shlvl);
int				error_bool(char *token_sp, char *token_sp1);
int				error_bool2(char *token_sp, char *token_sp1);
int				redir_bool(char *token_sp);
int				ft_find_paths(char **our_env);
int				is_alnum(char c);
int				proper_key(char *key);
int				check_last_fd(char **tokens, int *status, t_info *info);
void			inthandler(int sig);
void			quit_handler(int sig);
int				double_cond(char token);
void			ft_set_to_zero(int *i, int *quote, int *count, char *prev);
void			double_red(char **new, int *i);
void			single_red(char **new);
char			**ft_add_delim(char **new, char delim);
char			**tabjoin(char **tab1, char **tab2);
char			*ft_add_char(char **line, char c);
int				ft_strlen(char *line);
int				*io2(int *io, int fd1, int fd2);
int				next_semi(char **tokens);
char			**ft_tabdup(char **src);
void			ft_run_helper(char *token, char *program_name, int err);
#endif
