/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** my_realloc
*/

#include <stdlib.h>
#include "my_lib.h"

void *my_realloc(void *pointer, size_t memory_size, size_t original_size)
{
    size_t copy_size = 0;
    void *new_pointer = NULL;

    if (!pointer) {
        new_pointer = malloc(memory_size);
        if (!new_pointer)
            return NULL;
        return new_pointer;
    }
    new_pointer = malloc(memory_size);
    if (new_pointer) {
        copy_size = (original_size < memory_size) ?
            original_size : memory_size;
        new_pointer = my_memcpy(new_pointer, pointer, copy_size);
    } else {
        return NULL;
    }
    free(pointer);
    return new_pointer;
}
