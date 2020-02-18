# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 17:53:15 by ashishae          #+#    #+#              #
#    Updated: 2020/02/18 21:06:21 by ashishae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/ft_putstr.c srcs/main.c srcs/shell_loop.c\
srcs/ft_split.c srcs/pwd.c srcs/echo.c srcs/ft_cd.c\
srcs/after_norm_ft_exec.c srcs/exit.c srcs/tokens.c srcs/execute.c srcs/libft.c \
srcs/compare_tokens.c srcs/redirects.c srcs/env.c srcs/env_utils.c srcs/check_var.c \
srcs/ft_strdup.c srcs/ft_set_env.c srcs/ft_paths_args.c srcs/redir_handlers.c
TEST_SRCS = srcs/ft_putstr.c srcs/shell_loop.c\
srcs/ft_split.c srcs/pwd.c tests/test_shell_loop.c\
tests/test_pwd.c tests/test_ft_putstr.c srcs/env.c srcs/env_utils.c\
srcs/libft.c tests/test_environ.c srcs/ft_cd.c srcs/echo.c srcs/ft_exec.c\
srcs/exit.c tests/test_echo.c tests/test_cd.c tests/test_exec.c \
tests/test_redirect.c srcs/redirects.c srcs/execute.c srcs/tokens.c\
srcs/compare_tokens.c tests/test_compare_tokens.c tests/test_env_utils.c\
srcs/check_var.c tests/test_tokens.c
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -I includes -fsanitize=address

.PHONY: 	clean fclean all re bonus

all:		$(NAME)

.c.o:
			gcc $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			gcc -o $(NAME) $(OBJS) $(CFLAGS)

clean:
			rm -f $(OBJS) $(TEST_OBJS)
			rm -f *.gcno *.gcda *.gcov

fclean: 	clean
			rm -f $(NAME)
			rm -f test

re:			fclean all

run_tests:
			rm -f *.gcno *.gcda *.gcov
			gcc $(SRCS) $(CFLAGS) -coverage -o minishell
			cd tests ; ./int.sh

