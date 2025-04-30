# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:08:10 by nmeintje          #+#    #+#              #
#    Updated: 2025/04/29 13:48:24 by mdahlstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	./ft_isalpha.c \
		./ft_isdigit.c \
		./ft_isalnum.c \
		./ft_isascii.c \
		./ft_isprint.c \
		./ft_iswhitespace.c \
		./ft_strlen.c \
		./ft_memset.c \
		./ft_bzero.c \
		./ft_memcpy.c \
		./ft_memmove.c \
		./ft_strlcpy.c \
		./ft_strncpy.c \
		./ft_strcat.c \
		./ft_strlcat.c \
		./ft_toupper.c \
		./ft_tolower.c \
		./ft_max.c \
		./ft_strchr.c \
		./ft_strrchr.c \
		./ft_strcmp.c \
		./ft_strncmp.c \
		./ft_memchr.c \
		./ft_memcmp.c \
		./ft_strnstr.c \
		./ft_atoi.c \
		./ft_atof.c \
		./ft_atol.c \
		./ft_calloc.c \
		./ft_strdup.c \
		./ft_strcpy.c \
		./ft_substr.c \
		./ft_strjoin.c \
		./ft_strtrim.c \
		./ft_split.c \
		./ft_itoa.c \
		./ft_strmapi.c \
		./ft_striteri.c \
		./ft_putchar_fd.c \
		./ft_putstr_fd.c \
		./ft_putendl_fd.c \
		./ft_putnbr_fd.c \
		./ft_strequ.c \
		./get_next_line.c

OBJS = ${SRCS:.c=.o}

SRCSB =	./ft_lstadd_back_bonus.c \
		./ft_lstadd_front_bonus.c \
		./ft_lstclear_bonus.c \
		./ft_lstdelone_bonus.c \
		./ft_lstiter_bonus.c \
		./ft_lstlast_bonus.c \
		./ft_lstmap_bonus.c \
		./ft_lstnew_bonus.c \
		./ft_lstsize_bonus.c

OBJB = ${SRCSB:.c=.o}

HEAD = libft.h

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

bonus: .bonus

.bonus: $(NAME) ${OBJB}
	${AR} ${NAME} ${OBJB}
	@touch .bonus

LIBS = ranlib

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rcs

RM = rm -r

clean:
	rm -f ${OBJS}
	rm -f ${OBJB}

fclean:	clean
	rm	-f	${NAME}
	rm -f .bonus

re:	fclean all

rebonus: fclean bonus

.PHONY:	all clean fclean re bonus rebonus
