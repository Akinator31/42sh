/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** my_memset
*/

#include <stdlib.h>
#include "my_lib.h"

void *my_memset(void *pointer, int value, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        ((char *)pointer)[i] = value;
    }
    return pointer;
}
