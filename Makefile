SRC			= $(wildcard src/*.c)

OBJ			= ${SRC:.c=.o}

INC			= $(wildcard include/*.h)

NAME		= libsnafuENG.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

LDFLAGS		= -L. -lsnafuENG

all:		${NAME}

${NAME}:	${OBJ} ${INC}
			ar -rcs $@ ${OBJ}

.c.o:		${INC}
			${CC} ${CFLAGS} -I./include -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re