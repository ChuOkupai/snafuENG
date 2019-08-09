# Paths
BUILD_DIR	= build
INC_DIR		= include
SRC_DIR		= src

# Sources files
INC	:= $(wildcard ${INC_DIR}/*.h)
SRC	:= $(wildcard ${SRC_DIR}/*.c)
DEP	:= $(notdir ${SRC})
DEP	:= $(DEP:%.c=${BUILD_DIR}/%.d)
OBJ	:= $(DEP:.d=.o)
LIB	= libsnafuENG.a

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
LDFLAGS	= -L. -lsnafuENG

# Test
MAIN	?= test/main.c
EXEC	?= $(basename ${MAIN})
DEBUG	?= valgrind

echo:
	@echo "> INC:" ${INC}
	@echo "> SRC:" ${SRC}
	@echo "> OBJ:" ${OBJ}
	@echo "> DEP:" ${DEP}

all: ${LIB}

-include $(DEP)

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -I./${INC_DIR} -MD -c $< -o $@

${LIB}: ${OBJ}
	ar -rcs $@ ${OBJ}

${EXEC}: ${MAIN} ${INC} ${LIB}
	${CC} ${CFLAGS} -I./${INC_DIR} $< -o $@ ${LDFLAGS}

testd: ${EXEC} ${LIB}
	${DEBUG} ./$<

test: ${EXEC} ${LIB}
	./$<

clean:
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -f ${LIB} ${EXEC}

re: fclean all

.PHONY: all test clean fclean re