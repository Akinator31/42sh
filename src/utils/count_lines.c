/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** change_directory
*/

#include "utils.h"
#include <stdio.h>
#include <sys/types.h>

size_t count_lines(char *path)
{
    FILE *stream = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    size_t total = 0;

    if (!stream)
        return 0;
    while (getline(&line, &len, stream) != -1)
        total++;
    fclose(stream);
    return total;
}
