/*
** EPITECH PROJECT, 2025
** my_ctype
** File description:
** Checks if a character is alpha
*/

#include "my_lib.h"

int my_isalpha(char c)
{
    if ((c >= 'a') && (c <= 'z'))
        return 1;
    if ((c >= 'A') && (c <= 'Z'))
        return 1;
    if ((c >= '0') && (c <= '9'))
        return 1;
    return 0;
}
