/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** errno_manager
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "my_lib.h"

void errno_manager(int exec_return, char **command_element)
{
    char *error_to_string = NULL;

    if (exec_return != 0 && errno == ENOENT) {
        write(2, command_element[0], my_strlen(command_element[0]));
        write(2, ": Command not found.\n", 21);
        free_2d_array_of_char(command_element);
        exit(EXIT_FAILURE);
    } else if (exec_return != 0) {
        error_to_string = strerror(errno);
        write(2, command_element[0], my_strlen(command_element[0]));
        write(2, ": ", 2);
        write(2, error_to_string, my_strlen(error_to_string));
        write(2, ".\n", 2);
        free_2d_array_of_char(command_element);
        exit(EXIT_FAILURE);
    } else {
        return;
    }
}
