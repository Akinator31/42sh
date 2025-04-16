/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** skip_inhib_char
*/

#include "mysh.h"

int skip_inhib(char *str)
{
    int i = 0;
    int inhib = 0;

    while (str[i] != '\0' && inhib != 2) {
        if (str[i] == INIBITHORS_CHAR)
            inhib++;
        i++;
    }
    return i;
}
