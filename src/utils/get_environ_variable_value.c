/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** get_environ_variable
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "my_lib.h"

char *get_environ_variable_value(char ***envp, char *variable)
{
    char **env = *envp;
    int environ_variable_index =
        get_index_of_environment_variable(*envp, variable);
    char *variable_copy = NULL;
    char **token = NULL;
    char *value = NULL;

    if (environ_variable_index != -1) {
        variable_copy = my_strdup(env[environ_variable_index]);
        token = str_to_word_array(variable_copy, "=\n\t");
        if (token[1])
            value = my_strdup(token[1]);
        free_2d_array_of_char(token);
        free(variable_copy);
        return value;
    } else {
        return NULL;
    }
}
