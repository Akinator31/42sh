/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_inhib_len
*/

#include "mysh.h"

int get_inhib_len(char *str)
{
    int nb_inhib = 0;
    int i = 0;
    int len = 0;

    while (str[i] != '\0' && nb_inhib != 2) {
        if (str[i] == INIBITHORS_CHAR) {
            nb_inhib++;
            i++;
            continue;
        }
        len++;
        i++;
    }
    return len;
}
