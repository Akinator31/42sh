/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_put_str_minimize
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_lib.h"

void my_write_min(char *str, int output)
{
    char *string = my_strdup(str);

    for (int i = 0; string[i] != '\0'; i++)
        string[i] += 32;
    for (int i = 0; string[i] != '\0'; i++)
        write(output, &string[i], 1);
    write(output, '\0', 1);
    free(string);
}
