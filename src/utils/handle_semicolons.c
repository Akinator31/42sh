/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** handle_semicolons
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_lib.h"
#include "commands.h"
#include "utils.h"

static void execute_semicolon(char ***envp, char *command, int *error_code)
{
    int stdout_cpy = dup(STDOUT_FILENO);
    char **commands = str_to_word_array(command, ";\n\t");

    for (int i = 0; commands[i] != NULL; i++) {
        analyse_command(envp, commands[i], error_code);
        dup2(stdout_cpy, STDOUT_FILENO);
    }
    free_2d_array_of_char(commands);
}

int handle_semicolons(char *command, char ***envp, int *error_code)
{
    if (my_strstr(command, ";")) {
        execute_semicolon(envp, command, error_code);
        return 1;
    }
    return 0;
}
