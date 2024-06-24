# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 10:43:45 by asohrabi          #+#    #+#              #
#    Updated: 2024/06/24 10:43:27 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER	= -I ./include

FUNC =  src/atoi_utils.c \

OBJ = ${FUNC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@cc ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@make -C ./lib/libft
	@cc ${CFLAGS} ${OBJ} ${HEADER} -o ${NAME}

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re
