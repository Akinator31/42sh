/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** handle_semicolons
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include <stdio.h>

static int execute_semicolon(char ***envp, char *command, int *error_code,
    config_rc_t *config)
{
    int stdout_cpy = dup(STDOUT_FILENO);
    char **commands = str_to_word_array(command, ";\n\t");

    if (stdout_cpy == -1) {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; commands[i] != NULL; i++) {
        analyse_command(envp, commands[i], error_code, config);
        if (my_dup2(stdout_cpy, STDOUT_FILENO) == FAILURE)
            return FAILURE;
    }
    free_2d_array_of_char(commands);
    return SUCCESS;
}

int handle_semicolons(char *command, char ***envp, int *error_code,
    config_rc_t *config)
{
    if (my_strstr(command, ";")) {
        if (execute_semicolon(envp, command, error_code, config) == FAILURE)
            return FAILURE;
        return 1;
    }
    return 0;
}
