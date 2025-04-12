/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** my_put_str_minimize
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_lib.h"

void my_write_min(const char *str, int fd)
{
    char c = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
        write(fd, &c, 1);
    }
}
