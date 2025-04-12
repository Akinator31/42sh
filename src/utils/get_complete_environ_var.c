/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** get_complete_environ_var
*/

#include <stdlib.h>
#include "my_lib.h"

char *get_environ_var(const char *name, const char *value)
{
    int environ_variable_size = my_strlen(name) + my_strlen(value) + 2;
    char *environ_var = malloc(sizeof(char) * (environ_variable_size + 1));

    environ_var[0] = '\0';
    environ_var = my_strcat(environ_var, name);
    environ_var = my_strcat(environ_var, "=");
    environ_var = my_strcat(environ_var, value);
    environ_var[environ_variable_size] = '\0';
    return environ_var;
}
