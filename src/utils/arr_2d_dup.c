/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** arr_2d_dup
*/

#include <stdlib.h>
#include "my_lib.h"

char **duplicate_2d_char_array(char **array, int new_size)
{
    int i = 0;
    char **new_environ = malloc(sizeof(char *) * new_size);

    while (array[i]) {
        new_environ[i] = my_strdup(array[i]);
        i++;
    }
    new_environ[new_size - 1] = NULL;
    return new_environ;
}
