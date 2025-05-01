/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Utility functions for backtick command substitution
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "backtick.h"
#include "mysh.h"

static void *free_and_return_null(char *ptr)
{
    free(ptr);
    return NULL;
}

static char *read_from_pipe(int pipe_fd, int *error)
{
    char buffer[4096] = {0};
    size_t total_size = 0;
    ssize_t bytes_read = 0;
    char *output = NULL;

    output = read_pipe_output(pipe_fd, bytes_read, buffer, &total_size);
    if (!output) {
        *error = 1;
        return NULL;
    }
    if (total_size > 0 && output[total_size - 1] == '\n') {
        output[total_size - 1] = '\0';
    }
    return output;
}

static void restore_stdout(int original_stdout)
{
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
}

int setup_capture_pipes(int pipefd[2], int *original_stdout)
{
    if (pipe(pipefd) == -1)
        return 0;
    *original_stdout = dup(STDOUT_FILENO);
    if (*original_stdout == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return 0;
    }
    return 1;
}

void execute_child_command(int pipefd[2], char *cmd, char ***envp,
    config_rc_t *config)
{
    int error_code = 0;

    if (setup_child_process(pipefd) == EXIT_FAILURE)
        exit(EXIT_FAILURE);
    analyse_command(envp, cmd, &error_code, config);
    exit(error_code);
}

char *handle_parent_process(int pipefd[2], pid_t pid, int original_stdout)
{
    int error = 0;
    char *output = NULL;

    close(pipefd[1]);
    output = read_from_pipe(pipefd[0], &error);
    if (error)
        return NULL;
    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    restore_stdout(original_stdout);
    return output;
}

char *execute_and_capture_output(char *cmd, sh_t *sh_c)
{
    int pipefd[2];
    pid_t pid;
    int original_stdout;
    char *output = NULL;

    if (!setup_capture_pipes(pipefd, &original_stdout))
        return NULL;
    pid = fork();
    if (pid == -1) {
        cleanup_pipe_resources(pipefd, original_stdout);
        return NULL;
    }
    if (pid == 0) {
        execute_child_command(pipefd, cmd, sh_c->envp, sh_c->config);
    } else {
        output = handle_parent_process(pipefd, pid, original_stdout);
    }
    return output;
}

static char *process_backtick_command(backtick_params_t params,
    sh_t *sh_c)
{
    char *cmd_output = NULL;
    char *new_cmd = NULL;

    cmd_output = execute_and_capture_output(params.backtick_cmd, sh_c);
    free(params.backtick_cmd);
    if (!cmd_output)
        return free_and_return_null(params.processed_cmd);
    new_cmd = substitute_backtick(params.processed_cmd, params.backtick_pos,
        params.full_length, cmd_output);
    free(cmd_output);
    free(params.processed_cmd);
    if (!new_cmd)
        return NULL;
    return new_cmd;
}

char *find_backsticks(char *processed_cmd, char *backtick_pos,
    sh_t *sh_c)
{
    int cmd_length = 0;
    int full_length = 0;
    char *backtick_cmd = NULL;
    backtick_params_t params = {0};

    backtick_cmd = extract_backtick_command(backtick_pos, &cmd_length,
        &full_length);
    if (!backtick_cmd)
        return free_and_return_null(processed_cmd);
    params.processed_cmd = processed_cmd;
    params.backtick_cmd = backtick_cmd;
    params.backtick_pos = backtick_pos;
    params.full_length = full_length;
    return process_backtick_command(params, sh_c);
}
