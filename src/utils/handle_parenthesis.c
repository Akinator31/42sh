/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser util for parenthesis
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/my_lib.h"
#include "../../include/commands.h"
#include "../../include/utils.h"


static int count_parenthesis(
    char *command,
    char ***envp,
    int *error_code)
{
    int right_parenthesis = 0;
    int left_parenthesis = 0;

    for (int i = 0; command[i] != 0; i++) {
        if (command[i] == '(')
            right_parenthesis++;
        if (command[i] == ')')
            left_parenthesis++;
    }
    if (left_parenthesis != right_parenthesis) {
        if (left_parenthesis > right_parenthesis)
            write(2, "Too many )'s\n", 14);
        if (left_parenthesis < right_parenthesis)
            write(2, "Too many \('s\n", 15);
        return 1;
    }
    return 0;
}

int handle_parenthesis(
    char *command,
    char ***envp,
    int *error_code)
{
    if (count_parenthesis(command, envp, error_code))
        return 1;
    if (my_strstr(command, "(")) {
        check_valid_subshell(command, envp, error_code);
        return 0;
    }
    return 1;
}
