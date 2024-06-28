# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 16:14:08 by asohrabi          #+#    #+#              #
#    Updated: 2024/06/28 13:52:18 by asohrabi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER	= -I ./include

FUNC =  src/main.c src/utils.c src/init.c src/execute.c src/terminate.c \
		src/actions.c src/control.c \

OBJ = ${FUNC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@cc ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@cc ${CFLAGS} -O3 -pthread ${OBJ} ${HEADER} -o ${NAME}

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re
