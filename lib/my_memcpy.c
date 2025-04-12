/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** my_memcpy
*/

#include <stdlib.h>
#include "my_lib.h"

void *my_memcpy(void *dest, const void *src, size_t size)
{
    for (int i = 0; i < size; i++)
        ((char *)dest)[i] = ((char *)src)[i];
    return dest;
}
