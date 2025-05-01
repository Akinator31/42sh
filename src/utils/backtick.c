/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Backtick command substitution
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "backtick.h"

char *find_next_backtick(char *command)
{
    char *backtick = NULL;

    if (!command)
        return NULL;
    backtick = strchr(command, '`');
    return backtick;
}

char *extract_backtick_command(char *backtick_start, int *cmd_length,
    int *full_length)
{
    char *end_backtick = NULL;
    char *cmd = NULL;

    if (!backtick_start || backtick_start[0] != '`')
        return NULL;
    end_backtick = strchr(backtick_start + 1, '`');
    if (!end_backtick)
        return NULL;
    *cmd_length = end_backtick - (backtick_start + 1);
    *full_length = end_backtick - backtick_start + 1;
    cmd = malloc(*cmd_length + 1);
    if (!cmd)
        return NULL;
    strncpy(cmd, backtick_start + 1, *cmd_length);
    cmd[*cmd_length] = '\0';
    return cmd;
}

void cleanup_pipe_resources(int pipefd[2], int original_stdout)
{
    close(pipefd[0]);
    close(pipefd[1]);
    close(original_stdout);
}

int setup_child_process(int pipefd[2])
{
    close(pipefd[0]);
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        return EXIT_FAILURE;
    }
    close(pipefd[1]);
    return EXIT_SUCCESS;
}

char *substitute_backtick(char *original, char *start, int full_length,
    char *replacement)
{
    size_t orig_len = strlen(original);
    size_t repl_len = strlen(replacement);
    size_t offset = start - original;
    size_t new_len = orig_len - full_length + repl_len;
    char *new_cmd = NULL;

    if (!original || !start || !replacement)
        return NULL;
    new_cmd = malloc(new_len + 1);
    if (!new_cmd)
        return NULL;
    strncpy(new_cmd, original, offset);
    strcpy(new_cmd + offset, replacement);
    strcpy(new_cmd + offset + repl_len, start + full_length);
    return new_cmd;
}
