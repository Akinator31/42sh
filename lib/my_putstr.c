/*
** EPITECH PROJECT, 2025
** my_putstr.c
** File description:
** task02
*/

#include <unistd.h>
#include "my_lib.h"

void my_putstr(char const *str, int output)
{
    for (int i = 0; str[i] != '\0'; i++) {
        write(output, &str[i], 1);
    }
}
