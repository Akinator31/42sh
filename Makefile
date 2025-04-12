##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for minishell2 project
##

SRC = $(shell find . -type f -name "*.c" ! -path "./tests/*")
SRC_TESTS = $(shell find . -type f -name "*.c" ! -name "main.c")
LIB = $(shell find . -type f -name "*.a")
OBJ = 	$(SRC:%.c=build/%.o)
OBJ_DEBUG = 	$(SRC:%.c=build-debug/%.o)
OBJS_TESTS = $(SRC_TESTS:%.c=build-tests/%.o)
DEBUG_FLAGS = -g3 -Iinclude -fsanitize=address -Wextra
TEST_FLAGS = -Iinclude --coverage -lgcov -lcriterion
CFLAGS += -Iinclude
NAME = 42sh
DEBUG_NAME = debug
TEST_NAME = test_42_sh

build/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@

build-debug/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(DEBUG_FLAGS) -c $< -o $@

build-tests/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(TEST_FLAGS) -c $< -o $@

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)

.PHONY: $(DEBUG_NAME)
$(DEBUG_NAME): $(OBJ_DEBUG)
	gcc -o $(DEBUG_NAME) $(OBJ_DEBUG) $(LIB) $(DEBUG_FLAGS)

.PHONY: tests_run
tests_run: $(OBJS_TESTS)
	gcc -o $(TEST_NAME) $(OBJS_TESTS) $(TEST_FLAGS)
	./$(TEST_NAME)

.PHONY: show_test
show_test: tests_run
	mkdir -p coverage
	gcovr -r . --html --html-details -o coverage/index.html
	firefox coverage/index.html

.PHONY: clean
clean:
	find . -type f -name "*.o" -delete

.PHONY: fclean
fclean: clean
	rm -rf build
	rm -rf build-debug
	rm -rf build-tests
	rm -f $(NAME)
	rm -f $(DEBUG_NAME)
	rm -f $(TEST_NAME)
	rm -rf coverage
	$(shell find . -name "*.gcda" -delete)
	$(shell find . -name "*.gcno" -delete)

.PHONY: re
re: fclean all
.NOTPARALLEL: re
