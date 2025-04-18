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
#include <stdio.h>
#include "my_lib.h"
#include "utils.h"
#include "mysh.h"

int handle_simple_left_redirection(char *command, int *status)
{
    int fd = 0;
    char *input_file = my_strstr(command, "<");

    if (input_file) {
        if (check_meta_format(command, "<") == 0) {
            *status = 84;
            return 0;
        }
        *input_file = '\0';
        input_file = strtok(input_file + 1, " \n");
        fd = open(input_file, O_RDONLY);
        if (fd < 0) {
            *status = 84;
            printf("%s: No such file or directory.\n", input_file);
            return 0;
        }
        my_dup2(fd, STDIN_FILENO);
        close(fd);
    }
    return 1;
}

int handle_simple_right_redirection(char *command, int *status)
{
    int fd = 0;
    char *output_file = my_strstr(command, ">");

    if (output_file) {
        if (check_meta_format(command, ">") == 0) {
            *status = 84;
            return 0;
        }
        *output_file = '\0';
        output_file = strtok(output_file + 1, " \n");
        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (my_dup2(fd, STDOUT_FILENO) == FAILURE)
            return FAILURE;
        close(fd);
    }
    return 1;
}

int handle_double_right_redirection(char *command, int *status)
{
    int fd = 0;
    char *output_file = my_strstr(command, ">>");

    if (output_file) {
        if (check_meta_format(command, ">>") == 0) {
            *status = 84;
            return 0;
        }
        *output_file = '\0';
        output_file = strtok(output_file + 2, " \n");
        fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (my_dup2(fd, STDOUT_FILENO) == FAILURE)
            return FAILURE;
        close(fd);
    }
    return 1;
}
