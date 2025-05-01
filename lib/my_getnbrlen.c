/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_getnbrlen
*/

#include <stddef.h>
#include "my_lib.h"

size_t my_getnbrlen(int number, int base)
{
    size_t len = 0;

    if (base < 2 || base > 36)
        return 0;
    if (number == 0)
        return 1;
    if (number < 0 && base == 10) {
        len++;
        number = -number;
    }
    for (; number != 0; len++)
        number /= base;
    return len;
}
