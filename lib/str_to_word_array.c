/*
** EPITECH PROJECT, 2025
** LIB
** File description:
** str_to_word_array
*/

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "my_lib.h"

char **str_to_word_array(const char *string, const char *separators)
{
    size_t len = 0;
    char **result = NULL;
    char *work_string = NULL;
    char *token = NULL;

    if (!string || !separators)
        return NULL;
    work_string = my_strdup(string);
    token = strtok(work_string, separators);
    result = malloc(sizeof(char *));
    while (token) {
        result = my_realloc(result, STR * (len + 1), STR * len);
        result[len] = my_strdup(token);
        token = strtok(NULL, separators);
        len++;
    }
    result = my_realloc(result, STR * (len + 1), STR * len);
    result[len] = NULL;
    free(work_string);
    return result;
}
