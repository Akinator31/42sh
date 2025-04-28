/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser util for parenthesis
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/my_lib.h"
#include "../../include/commands.h"
#include "../../include/utils.h"

static int check_delims(
    char c)
{
    char delims[] = {";|><"};

    for (int i = 0; i != 4; i++) {
        if (delims[i] == c)
            return 1;
    }
    return 0;
}

static int check_parenthesis_mode(
    char *command,
    char ***envp,
    int *error_code)
{
    int count = 0;

    for (int j = 0; command[j] != 0; j++) {
        if (command[j] == '(')
            count++;
        if (check_delims(command[j]) == 1)
            break;
    }
    if (count > 1)
        return 1;
    return 0;
}

static int valid_prompt(
    char *command)
{
    int i = 0;

    for (; command[i] != ')'; i++)
        continue;
    i++;
    for (; command[i] != 0; i++) {
        if (command[i] == SPACE || command == NULL || command[i] == NEW_LINE)
            continue;
        return -1;
    }
    return 0;
}

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
            write(2, "Too many \('s\n", 14);
        return 1;
    }
    return 0;
}

int handle_parenthesis(
    char *command,
    char ***envp,
    int *error_code)
{
    if (count_parenthesis(command, envp, error_code) == 1)
        return -1;
    if (valid_prompt(command) == -1) {
        write(2, "Parse Error near )\n", 20);
        return -1;
    }
    return check_parenthesis_mode(command, envp, error_code);
}
