# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeorgan <fgeorgan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 10:46:18 by fgeorgan          #+#    #+#              #
#    Updated: 2021/05/02 17:26:10 by fgeorgan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = all clean fclean re bonus
NAME = libft.a
RM = rm -f
OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32
SRC = ft_bzero.c \
ft_strdup.c \
ft_atoi.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_strchr.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_tolower.c \
ft_toupper.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
get_next_line_utils.c \
get_next_line.c \
ft_atof.c \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c \
ft_dlist_new.c \
ft_dlist_add.c 

all:	$(NAME)
$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ) libft.h get_next_line.h
clean:
	$(RM) $(OBJ)
fclean:	clean
	$(RM) $(NAME)
re:	fclean all