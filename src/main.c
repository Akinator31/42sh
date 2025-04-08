/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** main
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"

int handle_output_command(int result_command, char *buffer, char ***envp)
{
    if (result_command == EXIT) {
        free(buffer);
        return EXIT;
    }
    if (result_command == NORMAL && isatty(stdin->_fileno))
        print_prompt(*envp);
    if (result_command == NOTHING)
        return 0;
    return 0;
}

int mysh(char ***envp, int *error_code)
{
    int stdin_cpy = duplicate_file_descriptor(STDIN_FILENO);
    int stdout_cpy = duplicate_file_descriptor(STDOUT_FILENO);
    int result_command = 0;
    char *buffer = NULL;
    size_t len = 0;

    if (isatty(stdin->_fileno))
        print_prompt(*envp);
    while (getline(&buffer, &len, stdin) != -1) {
        result_command = analyse_command(envp, buffer, error_code);
        restore_stdin_stdout_fd(stdin_cpy, stdout_cpy);
        if (handle_output_command(result_command, buffer, envp)) {
            close_fds(2, stdin_cpy, stdout_cpy);
            return EXIT;
        }
    }
    close_fds(2, stdin_cpy, stdout_cpy);
    free(buffer);
    return EXIT_EOF;
}

int main(int ac, char **av, char **envp)
{
    int mysh_exit_status = 0;
    int mysh_tty_exit_status = 0;
    char **env = NULL;
    int error_code = 0;

    if (ac > 1)
        return 84;
    env = duplicate_2d_char_array(envp, get_2d_arr_len(envp) + 1);
    mysh_exit_status = mysh(&env, &error_code);
    if (mysh_exit_status == EXIT_EOF && isatty(stdin->_fileno))
        write(1, "exit\n", 5);
    free_2d_array_of_char(env);
    return error_code;
}
