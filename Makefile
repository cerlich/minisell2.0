.PHONY = all clean fclean re

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEAD = minishell.h

SRCS =	main.c \
		gnl.c \
		declare.c \
		signals.c \
		exit.c \
		pwd_env_echo.c \
		cd.c \
		export.c \
		utils_1.c \
		utils_2.c \
		unset.c \
		utils_3.c \
		redirect.c \
		parser.c \
		parser_dollar.c \
		parser_pipe_semicolon.c \
		parser_quota_redirect.c \
		exec_commands.c \
		preparser.c \
		pipe.c \
		redirect_err_quota.c

OBJS =$(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -o $(NAME)

$(OBJS) : %.o : %.c $(HEAD)

$(LIBFT):
	(cd libft; make all)

clean :
	(cd libft; make clean)
	rm -f $(OBJS)

fclean : clean
	(cd libft; make fclean)
	rm -f $(NAME)

re : fclean all