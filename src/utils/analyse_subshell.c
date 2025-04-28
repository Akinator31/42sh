/*
** EPITECH PROJECT, 2025
** header
** File description:
** analyse subshell
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "../../include/my_lib.h"
#include "../../include/mysh.h"
#include "../../include/utils.h"
#include <sys/wait.h>
#include "../../include/commands.h"

static int create_subshell(
    char *sub_line,
    char ***envp,
    int *error_code)
{
    pid_t pid = fork();
    int status;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        analyse_command(envp, sub_line, error_code, 0);
        exit(pid);
    }
    if (pid != 0)
        waitpid(pid, &status, WCONTINUED);
    return 0;
}

static void handle_subshell(
    char ***envp,
    char *command,
    subshell_t *subshell,
    int *error_code)
{
    int command_length = 0;
    int i = 0;
    int j = 0;
    char *line = NULL;

    for (int i = 0; command[i] != '('; i++)
        continue;
    for (j = i + 1; command[j] != ')'; j++)
        command_length++;
    i++;
    line = malloc(sizeof(char) * command_length + 1);
    memset(line, 0, command_length + 1);
    for (int x = 0; i != j; i++) {
        line[x] = command[i];
        x++;
    }
    create_subshell(line, envp, error_code);
    free(line);
}

int analyse_subshell(
    char *command,
    char ***envp,
    int *error_code)
{
    subshell_t subshell = {0};
    int save_return;
    int i = 0;

    if (strstr(command, "(")) {
        save_return = handle_parenthesis(command, envp, error_code);
        if (save_return == -1)
            return -1;
        handle_subshell(envp, command, &subshell, error_code);
        for (; command[i] != ')'; i++)
            continue;
        return i + 1;
    }
    return 0;
}
