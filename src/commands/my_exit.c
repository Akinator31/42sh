/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** exit
*/

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <mysh.h>
#include "my_lib.h"
#include "utils.h"

int my_is_strdigit(char *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    if (str[0] == '-')
        i++;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int check_expression_syntax(char **commands, int nb_args, int *error_code)
{
    if (nb_args == 2 && my_strlen(commands[1]) == 1
        && commands[1][0] == '-') {
        write(2, "exit: Expression Syntax.\n", 25);
        *error_code = 84;
        return 1;
    }
    if (nb_args > 2 || (!my_is_strdigit(commands[1])
        && commands[1][0] != '-')) {
        write(2, "exit: Expression Syntax.\n", 25);
        *error_code = 84;
        return 1;
    }
    return 0;
}

void handle_exit_number(char **commands, int nb_args,
    int *error_code, exit_status_t *status)
{
    int exit_code = 0;

    if (check_expression_syntax(commands, nb_args, error_code))
        return;
    if (!my_is_strdigit(commands[1] + 1) && commands[1][0] == '-') {
        write(2, "exit: Badly formed number.\n", 27);
        *error_code = 84;
    } else {
        exit_code = my_getnbr(commands[1]);
        *error_code = exit_code;
        *status = EXIT;
    }
}

bool is_exit_command(sh_t *sh_st, exit_status_t *status)
{
    char **commands = my_str_to_word_array(sh_st->command, " ");
    int nb_args = get_2d_arr_len(commands);

    if (my_strlen(sh_st->command) <= 1)
        return false;
    if (is_good_cmd("exit", commands[0])) {
        if (nb_args > 1) {
            handle_exit_number(commands, nb_args, sh_st->error_code, status);
            return true;
        }
        *status = EXIT;
        return true;
    }
    return false;
}
