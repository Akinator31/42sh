/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strisuppercase
*/

#include "my_lib.h"
#include <stdbool.h>

bool my_strisuppercase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (my_isalpha(str[i]) == 1 &&
        !(str[i] >= 'A' && str[i] <= 'Z'))
            return false;
        i++;
    }
    return true;
}
