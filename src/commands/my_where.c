/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_where
*/

#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void check_if_valid(char *cmd, char *token)
{
    char *file = NULL;

    file = malloc(strlen(cmd) + strlen(token) + 3);
    strcat(file, token);
    strcat(file, "/");
    strcat(file, cmd);
    if (access(file, X_OK) == 0)
        printf("%s\n", file);
    free(file);
}

static void find_binaries(sh_t *sh_st)
{
    char *dup = NULL;
    char **commands = str_to_word_array(sh_st->command, " \t\v");
    char *home = get_environ_variable_value(sh_st->envp, "PATH");

    if (get_2d_arr_len(commands) < 2) {
        free_2d_array_of_char(commands);
        *(sh_st->error_code) = 84;
        return;
    }
    for (int i = 1; commands[i] != NULL; i++) {
        dup = strdup(home);
        for (char *token = strtok(dup, ":"); token; token = strtok(NULL, ":"))
            check_if_valid(commands[i], token);
    }
    free_2d_array_of_char(commands);
    free(dup);
    free(home);
}

bool is_where_command(sh_t *sh_st, exit_status_t *status)
{
    if (is_good_cmd("where", sh_st->command)) {
        find_binaries(sh_st);
        *status = NORMAL;
        return true;
    }
    return false;
}
