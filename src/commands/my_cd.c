/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** cd
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysh.h"
#include "my_lib.h"
#include "utils.h"
#include "commands.h"

static const my_cd_t my_flags_arr[] = {
    {'~', &cd_to_directory, "HOME"},
    {'-', &cd_to_directory, "OLDPWD"},
    {'$', &cd_to_directory, NULL},
    {'?', NULL, NULL},
};

static void my_cd(char ***envp, char *command, int *error_code)
{
    char **command_element = str_to_word_array(command, " \n\t");
    int nb_args = get_2d_arr_len(command_element);

    if (is_too_much_args(nb_args, command_element, error_code))
        return;
    for (int i = 0; my_flags_arr[i].f; i++) {
        if (nb_args == 1) {
            cd_to_directory(envp, "HOME", error_code, 1);
            free_2d_array_of_char(command_element);
            return;
        }
        if (command_element[1][0] == my_flags_arr[i].flag) {
            my_flags_arr[i].f(envp, my_flags_arr[i].variable, error_code, 1);
            free_2d_array_of_char(command_element);
            return;
        }
    }
    cd_to_directory(envp, command_element[1], error_code, 0);
    free_2d_array_of_char(command_element);
}

bool is_cd_command(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    if (is_good_cmd("cd", command)) {
        my_cd(envp, command, error_code);
        *status = NORMAL;
        return true;
    }
    return false;
}
