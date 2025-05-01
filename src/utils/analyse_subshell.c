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
#include <string.h>
#include "mysh.h"
#include "utils.h"
#include <sys/wait.h>

static int create_subshell(
    char *sub_line,
    char ***envp,
    int *error_code,
    sh_t *sh_st)
{
    pid_t pid = fork();
    int status;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        analyse_command(sh_st->envp, sub_line, error_code, sh_st->config);
        exit(pid);
    }
    if (pid != 0)
        waitpid(pid, &status, WCONTINUED);
    return 0;
}

static void handle_subshell(sh_t *sh_st, subshell_t *subshell)
{
    int command_length = 0;
    int i = 0;
    int j = 0;
    char *line = NULL;

    for (int i = 0; sh_st->command[i] != '('; i++)
        continue;
    for (j = i + 1; sh_st->command[j] != ')'; j++)
        command_length++;
    i++;
    line = malloc(sizeof(char) * command_length + 1);
    memset(line, 0, command_length + 1);
    for (int x = 0; i != j; i++) {
        line[x] = sh_st->command[i];
        x++;
    }
    create_subshell(line, sh_st->envp, sh_st->error_code, sh_st);
    free(line);
}

int analyse_subshell(sh_t *sh_st, bool *is_subshell)
{
    subshell_t subshell = {0};
    int save_return;
    int i = 0;

    if (strstr(sh_st->command, "(")) {
        *is_subshell = true;
        save_return = handle_parenthesis(sh_st->command, sh_st->envp,
            sh_st->error_code);
        if (save_return == -1)
            return -1;
        handle_subshell(sh_st, &subshell);
        for (; sh_st->command[i] != ')'; i++)
            continue;
        return i + 1;
    }
    return 0;
}
