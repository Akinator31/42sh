/*
** EPITECH PROJECT, 2025
** my_strcmp.c
** File description:
** task06
*/

#include <stdlib.h>
#include "my_lib.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    int result = 0;

    if (!s1 || !s2)
        return -1;
    for (int i = 0; (s1[i] != '\0') || (s2[i] != '\0'); i++) {
        if (s1[i] != s2[i]) {
            result = s1[i] - s2[i];
            return result;
        }
    }
    result = s1[i] != s2[i];
    return result;
}
