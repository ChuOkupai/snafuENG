SRC			= $(wildcard src/*.c)

OBJ			= ${SRC:.c=.o}

INC			= $(wildcard include/*.h)

NAME		= libsnafuENG.a

SRC_MAIN	= test/main.c

MAIN		= main.out

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

LDFLAGS		= -L. -lsnafuENG

all:		${NAME}

${NAME}:	${OBJ} ${INC}
			ar -rcs $@ ${OBJ}

.c.o:		${INC}
			${CC} ${CFLAGS} -I./include -c $< -o ${<:.c=.o}

${MAIN}:	${SRC_MAIN} ${INC} ${NAME}
			${CC} ${CFLAGS} -I./include $< -o $@ ${LDFLAGS}

test:		${MAIN} ${NAME}
			./$<

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME} ${MAIN}

re:			fclean all

.PHONY:		all test clean fclean re