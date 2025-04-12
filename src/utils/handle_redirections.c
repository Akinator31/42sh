/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** handle_redirections
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "my_lib.h"
#include "utils.h"

void handle_simple_left_redirection(char *command)
{
    int fd = 0;
    char *input_file = my_strstr(command, "<");

    if (input_file) {
        *input_file = '\0';
        input_file = strtok(input_file + 1, " \n");
        fd = open(input_file, O_RDONLY);
        my_dup2(fd, STDIN_FILENO);
        close(fd);
    }
}

void handle_simple_right_redirection(char *command)
{
    int fd = 0;
    char *output_file = my_strstr(command, ">");

    if (output_file) {
        *output_file = '\0';
        output_file = strtok(output_file + 1, " \n");
        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        my_dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void handle_double_right_redirection(char *command)
{
    int fd = 0;
    char *output_file = my_strstr(command, ">>");

    if (output_file) {
        *output_file = '\0';
        output_file = strtok(output_file + 2, " \n");
        fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        my_dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}
