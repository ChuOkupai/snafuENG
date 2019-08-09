# Paths
INC_DIR			= include
SRC_DIR			= src
OBJ_DIR			= obj
DEP_DIR			= ${OBJ_DIR}/dep

# Sources files
INC				:= $(wildcard ${INC_DIR}/*.h)
SRC				:= $(wildcard ${SRC_DIR}/*.c)
OBJ				:= $(notdir ${SRC})
DEP				:= $(OBJ:%.c=${DEP_DIR}/%.d)
OBJ				:= $(OBJ:%.c=${OBJ_DIR}/%.o)
LIB				= libsnafuENG.a

# Compilation
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
DFLAGS			= -MMD -MF ${DEP_DIR}/$*.d
LDFLAGS			= -L. -lsnafuENG

# Test
MAIN			?= test/main.c
EXEC			?= $(basename ${MAIN})
DEBUG			?= valgrind

all:			${LIB}

${OBJ_DIR}:
				mkdir $@ ${DEP_DIR}

${OBJ_DIR}/%.o:	${SRC_DIR}/%.c | ${OBJ_DIR}
				${CC} ${CFLAGS} -c -I./${INC_DIR} $< -o $@ ${DFLAGS}

${LIB}:			${OBJ}
				ar -rcs $@ ${OBJ}

${EXEC}:		${MAIN} ${INC} ${LIB}
				${CC} ${CFLAGS} -I./${INC_DIR} $< -o $@ ${LDFLAGS}

test:			${EXEC} ${LIB}
				./$<

testd:			${EXEC} ${LIB}
				${DEBUG} ./$<

clean:
				rm -rf ${OBJ_DIR}

fclean:			clean
				rm -f ${LIB} ${EXEC}

re:				fclean all

-include		$(DEP)

.PHONY:			all test testd clean fclean re