/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** strcat_malloc
*/

#include <stdlib.h>
#include <string.h>

char *my_strcat_malloc(char *str1, char *str2)
{
    char *str = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    int i = 0;
    int i2 = 0;

    while (str1[i2] != '\0') {
        str[i] = str1[i2];
        i2++;
        i++;
    }
    i2 = 0;
    while (str2[i2] != '\0') {
        str[i] = str2[i2];
        i2++;
        i++;
    }
    str[i] = '\0';
    return str;
}