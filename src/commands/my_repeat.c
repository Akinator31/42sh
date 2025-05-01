/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_repeat
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"
#include "commands.h"

static int count_words_in_str(char *str, char *delim)
{
    int count = 0;
    char *dup_string = strdup(str);
    char *token = strtok(dup_string, delim);

    while (token != NULL) {
        count++;
        token = strtok(NULL, delim);
    }
    free(dup_string);
    return count;
}

static void process_repeat_command(sh_t *sh_st, exit_status_t *status)
{
    char **cmd_args = str_to_word_array(sh_st->command, " \n\t");
    int nb_args = count_words_in_str(sh_st->command, " \n\t");
    int repeat_count = 0;

    if (nb_args >= 3) {
        repeat_count = atoi(cmd_args[1]);
        if (repeat_count < 0) {
            write(2, "repeat: Invalid repeat count.\n", 31);
            free_2d_array_of_char(cmd_args);
            return;
        }
        sh_st->command = sh_st->command +
            strlen(cmd_args[0]) + strlen(cmd_args[1]) + 2;
        for (int i = 0; i < repeat_count; i++)
            my_exec(sh_st, status, 0);
    } else {
        *(sh_st->error_code) = 84;
        fprintf(stderr, "repeat: Too few arguments.\n");
    }
    free_2d_array_of_char(cmd_args);
}

bool is_repeat_command(sh_t *sh_st, exit_status_t *status)
{
    if (is_good_cmd("repeat", sh_st->command)) {
        process_repeat_command(sh_st, status);
        *status = NORMAL;
        return true;
    }
    return false;
}
