# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 17:53:15 by ashishae          #+#    #+#              #
#    Updated: 2020/03/02 21:07:46 by ashishae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/ft_putstr.c srcs/main.c srcs/shell_loop.c srcs/shell_loop2.c\
srcs/ft_split.c srcs/pwd.c srcs/echo.c srcs/ft_cd.c\
srcs/after_norm_ft_exec.c srcs/exit.c srcs/tokens2.c srcs/execute.c srcs/libft.c \
srcs/compare_tokens.c srcs/redirects.c srcs/env.c srcs/env_utils.c srcs/check_var.c \
srcs/ft_strdup.c srcs/ft_set_env.c srcs/ft_paths_args.c srcs/redir_handlers2.c \
srcs/get_next_line.c srcs/error_handler.c srcs/ft_itoa.c srcs/rearr_var.c \
srcs/all_env.c srcs/ft_strjoin.c srcs/ft_atoi.c srcs/env2.c srcs/bool_ch.c \
srcs/ft_paths.c srcs/env_utils2.c srcs/resolve_redirs.c srcs/quotes_funct.c \
srcs/tab_functions.c srcs/utils.c srcs/handlers_dispatch.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

CFLAGS = -Wall -Wextra -Werror -I includes

.PHONY: 	clean fclean all re

all:		$(NAME)

.c.o:
			gcc $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			gcc -o $(NAME) $(OBJS) $(CFLAGS)

clean:
			rm -f $(OBJS) $(TEST_OBJS)

fclean: 	clean
			rm -f $(NAME)

re:			fclean all