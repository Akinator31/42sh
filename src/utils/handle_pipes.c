/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell2-pavel.de-wavrechin
** File description:
** handle_pipes
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "commands.h"
#include "my_lib.h"
#include "utils.h"

static void is_next_commands_not_null(char *commands, int pipefd[2])
{
    if (commands != NULL) {
        my_dup2(pipefd[STDOUT_FILENO], STDOUT_FILENO);
        close(pipefd[STDOUT_FILENO]);
    }
}

static void handle_fork_error(pid_t pid)
{
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

int count_nb_pipe(char *command)
{
    int nb_pipe = 0;

    for (size_t i = 0; command[i]; i++) {
        if (command[i] == '|')
            nb_pipe++;
    }
    return nb_pipe;
}

static void execute_pipe(char ***envp, char **commands, int *error_code)
{
    int pipefd[2];
    pid_t pid;
    int fd_in = STDIN_FILENO;

    for (int i = 0; commands[i] != NULL; i++) {
        pipe(pipefd);
        pid = fork();
        handle_fork_error(pid);
        if (pid == 0) {
            dup2(fd_in, STDIN_FILENO);
            is_next_commands_not_null(commands[i + 1], pipefd);
            analyse_command(envp, commands[i], error_code);
            exit(EXIT_SUCCESS);
        } else {
            close(pipefd[STDOUT_FILENO]);
            fd_in = pipefd[STDIN_FILENO];
        }
    }
    waitpid(pid, NULL, 0);
}

int handle_pipes(char *command, char ***envp, int *error_code)
{
    char **commands = NULL;
    int nb_pipes = count_nb_pipe(command);
    int nb_elements_in_cmd = 0;

    if (my_strstr(command, "|")) {
        commands = str_to_word_array(command, "|\n\t");
        nb_elements_in_cmd = get_2d_arr_len(commands);
        if (nb_pipes != nb_elements_in_cmd - 1) {
            *error_code = 1;
            write(2, "Invalid null command.\n", 22);
            return 1;
        }
        execute_pipe(envp, commands, error_code);
        free_2d_array_of_char(commands);
        return 1;
    }
    return 0;
}
