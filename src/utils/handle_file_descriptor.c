/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** duplicate_file_descriptor
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

void close_fds(int nb_elements, ...)
{
    va_list args;

    va_start(args, nb_elements);
    for (size_t i = 0; i < nb_elements; i++)
        close(va_arg(args, int));
    va_end(args);
}

int duplicate_file_descriptor(int fd)
{
    int fd_copy = dup(fd);

    if (fd_copy == -1) {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    return fd_copy;
}

void restore_stdin_stdout_fd(int stdin_cpy, int stdout_cpy)
{
    my_dup2(stdin_cpy, STDIN_FILENO);
    my_dup2(stdout_cpy, STDOUT_FILENO);
}
