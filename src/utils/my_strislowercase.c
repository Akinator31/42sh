/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strislowercase
*/

#include "my_lib.h"
#include <stdbool.h>

bool my_strislowercase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (my_isalpha(str[i]) == 1 &&
        !(str[i] >= 'a' && str[i] <= 'z'))
            return false;
        i++;
    }
    return true;
}
