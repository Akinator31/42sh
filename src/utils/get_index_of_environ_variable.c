/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** get_index_of_environ_variable
*/

#include <string.h>
#include <stdlib.h>
#include "my_lib.h"

int get_index_of_environment_variable(char **envp, char *environment_variable)
{
    int i = 0;
    char *line = NULL;

    while (envp[i]) {
        line = my_strdup(envp[i]);
        if (my_strcmp(strtok(line, "="), environment_variable) == 0) {
            free(line);
            return i;
        }
        free(line);
        i++;
    }
    return -1;
}
