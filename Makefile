# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 22:02:20 by sunpark           #+#    #+#              #
#    Updated: 2021/01/24 05:52:44 by hyukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c tokenize/cmd_io.c tokenize/tokenlst_init.c \
		  tokenize/cmdlst_util.c tokenize/cmdlst_init.c tokenize/token_utils.c \
		  tokenize/cmdlst_util2.c tokenize/token_utils2.c \
		  env/envlst.c env/envlst_util.c env/env_util.c env/path.c \
		  execute/exec.c execute/handle_fd.c execute/handle_pipe.c \
		  util/free.c util/error.c util/util.c util/util2.c util/signal.c \
		  util/gnl.c util/free2.c \
		  command/ft_pwd.c command/ft_cd.c command/ft_env.c	command/ft_export.c \
		  command/ft_unset.c command/ft_echo.c command/ft_exit.c

SRCDIR	= ./srcs/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

INCDIR	= ./includes/
LIBDIR	= ./libft/
LIBNAME	= libft.a

NAME	= minishell

GCC		= gcc
GCCFLAG	= -g3 -Wall -Wextra -Werror
RM		= rm -f

%.o:		%.c
			$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME):	$(LIBNAME) $(MLXNAME) $(OBJS) $(MOBJS)
			$(GCC) $(GCCFLAG) -I$(INCDIR) -o $(NAME) $(OBJS) $(LIBNAME)

$(LIBNAME):
			$(MAKE) -C $(LIBDIR) bonus
			@cp $(addprefix $(LIBDIR), $(LIBNAME)) $(LIBNAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME) $(LIBNAME)
			$(MAKE) -C $(LIBDIR) fclean

re:			fclean all

.PHONY:		all clean fclean re
