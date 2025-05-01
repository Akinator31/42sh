##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for 42sh project
##

SRC_DIR     	=	src
LIB_DIR     	=	lib
TESTS_DIR		=	tests
BUILD_DIR   	=	build
BUILD_DEBUG 	=	build-debug
BUILD_TESTS 	=	build-tests
INCLUDE_DIRS	=	include

SRC          	=	$(shell find $(SRC_DIR) -name "*.c")
TESTS        	=	$(shell find . -name "*.c" ! -name "main.c" \
                        -not -path "*/bonus/*")
LIB_SRC      	=	$(shell find $(LIB_DIR) -name "*.c")

OBJ          	= 	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LIB_OBJ      	= 	$(LIB_SRC:$(LIB_DIR)/%.c=$(BUILD_DIR)/lib/%.o)
OBJ_DEBUG    	= 	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DEBUG)/%.o)
OBJ_TESTS    	= 	$(TESTS:$(TESTS_DIR)/%.c=$(BUILD_TESTS)/%.o)

CC           	= 	gcc
INCLUDE      	= 	$(INCLUDE_DIRS:%=-I%)
CFLAGS       	= 	-Wall -Wextra $(INCLUDE) -Wno-unused-parameter
DEBUG_FLAGS  	= 	-fsanitize=address -g3 $(CFLAGS)
TEST_FLAGS   	= 	$(CFLAGS) --coverage -lgcov -lcriterion

NAME         	= 	42sh
DEBUG_NAME   	= 	debug
TESTS_NAME   	= 	tests_42sh

COLOR_RED		=     \033[1;31m
COLOR_ORANGE	=     \033[1;33m
COLOR_YELLOW	=     \033[1;33m
COLOR_GREEN		=     \033[1;32m
COLOR_BLUE		=     \033[1;34m
COLOR_PURPLE	=     \033[1;35m
COLOR_CYAN		=     \033[1;36m
COLOR_WHITE		=     \033[1;37m
COLOR_RESET		=     \033[0m

all: $(NAME)

$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_RED)Building library object $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_RED)Building $<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DEBUG)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_CYAN)Building $< for debugging$(COLOR_RESET)"
	@$(CC) $(DEBUG_FLAGS) -c $< -o $@

$(BUILD_TESTS)/%.o: tests/%.c
	@mkdir -p $(dir $@)
	@echo "$(COLOR_PURPLE)Building $< for testing$(COLOR_RESET)"
	@$(CC) $(TEST_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB_OBJ)
	@echo "$(COLOR_RED)Linking $(NAME)$(COLOR_RESET)"
	@$(CC) -o $(NAME) $(OBJ) $(LIB_OBJ) $(CFLAGS)
	@echo "$(COLOR_GREEN)Project built successfully!$(COLOR_RESET)"

$(DEBUG_NAME): $(OBJ_DEBUG) $(LIB_OBJ)
	@echo "$(COLOR_CYAN)Linking $(DEBUG_NAME)$(COLOR_RESET)"
	@$(CC) -o $(DEBUG_NAME) $(OBJ_DEBUG) $(LIB_OBJ) $(DEBUG_FLAGS)
	@echo "$(COLOR_GREEN)Debug build completed!$(COLOR_RESET)"

$(TESTS_NAME): $(OBJ_TESTS) $(LIB_OBJ)
	@echo "$(COLOR_PURPLE)Linking $(TESTS_NAME)$(COLOR_RESET)"
	@$(CC) -o $(TESTS_NAME) $(OBJ_TESTS) $(TEST_FLAGS)
	@echo "$(COLOR_GREEN)Tests build completed!$(COLOR_RESET)"

tests_run: $(TESTS_NAME)
	@echo "$(COLOR_RED)Running tests...$(COLOR_RESET)"
	@./$(TESTS_NAME)

show_test: tests_run
	@mkdir -p coverage
	@gcovr -r . --html --html-details -o coverage/index.html
	@firefox coverage/index.html

clean:
	@$(RM) -r $(BUILD_DIR) $(BUILD_DEBUG) $(BUILD_TESTS)
	@echo "$(COLOR_GREEN)Object files cleaned!$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME) $(DEBUG_NAME) $(TESTS_NAME)
	@$(RM) -r $(BUILD_DIR) $(BUILD_DEBUG) $(BUILD_TESTS)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@echo "$(COLOR_GREEN)Project cleaned!$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re tests_run show_test
