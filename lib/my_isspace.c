/*
** EPITECH PROJECT, 2025
** my_ctype
** File description:
** Checks if a character is space
*/

#include "my_lib.h"

int my_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\v')
        return 1;
    return 0;
}
