/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** free_2d_array_of_char
*/

#include <stdlib.h>

void free_2d_array_of_char(char **arr)
{
    if (!arr || !*arr)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}
