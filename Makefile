# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 17:53:15 by ashishae          #+#    #+#              #
#    Updated: 2020/02/03 15:18:16 by ashishae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/ft_putstr.c srcs/get_next_line.c srcs/main.c srcs/shell_loop.c\
srcs/ft_split.c srcs/get_next_line_utils.c srcs/pwd.c
TEST_SRCS = srcs/ft_putstr.c srcs/get_next_line.c srcs/shell_loop.c\
srcs/ft_split.c srcs/get_next_line_utils.c srcs/pwd.c tests/test_shell_loop.c\
tests/test_pwd.c
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -I includes

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

run_tests:	$(TEST_OBJS)
			gcc $(CFLAGS) $(TEST_SRCS) -o test -coverage -lcriterion && ./test && gcovr