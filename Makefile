# DIRECTORIES
DEP_DIR	= dep
INC_DIR	= inc
OBJ_DIR	= obj
SRC_DIR	= src

# FILES
INC		:= $(wildcard $(INC_DIR)/*.h)
SRC		:= $(wildcard $(SRC_DIR)/*.c)
OBJ		:= $(notdir $(SRC))
DEP		:= $(OBJ:%.c=$(DEP_DIR)/%.d)
OBJ		:= $(OBJ:%.c=$(OBJ_DIR)/%.o)
LIB		= libsnafuENG.a

# COMPILATION
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
DFLAGS	= -MP -MMD -MF $(DEP_DIR)/$*.d -MT '$@'
LDFLAGS	= -L. -lsnafuENG

# TEST
MAIN	= test/main.c
EXEC	= $(basename $(MAIN))
DEBUG	= valgrind

$(LIB): $(OBJ)
	ar -rcs $@ $(OBJ)

all: $(LIB)

test: $(EXEC) $(LIB)
	./$<

debug: $(EXEC) $(LIB)
	$(DEBUG) ./$<

clean:
	rm -rf $(DEP_DIR) $(OBJ_DIR)

fclean: clean
	rm -f $(LIB) $(EXEC)

re: fclean all

$(DEP_DIR):
	mkdir $@

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DEP_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -c -I./$(INC_DIR) $< -o $@

$(EXEC): $(MAIN) $(INC) $(LIB)
	$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@ $(LDFLAGS)

-include $(DEP)

.PHONY: all test debug clean fclean re