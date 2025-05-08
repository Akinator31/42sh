/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** set variable
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_lib.h"
#include "utils.h"
#include "mysh.h"

static int incorrect_first_char(char **cmd_args)
{
    if (!(my_isalpha(cmd_args[1][0]) || cmd_args[1][0] == '_') ||
    (cmd_args[1][0] >= '0' && cmd_args[1][0] <= '9')) {
        write(2, "set: Variable name must begin with a letter.\n", 46);
        return false;
    }
    return true;
}

static bool error_nb_args(char ***envp, bool is_correct_cmd,
    int nb_args, char **cmd_args)
{
    if (is_correct_cmd && (nb_args > 3 || nb_args == 1)) {
        if (nb_args > 3)
            write(2, "env: Too many arguments.\n", 25);
        if (nb_args == 1)
            env(*envp);
        free_2d_array_of_char(cmd_args);
        return false;
    }
    if (!incorrect_first_char(cmd_args))
        return false;
    for (int i = 0; cmd_args[1][i] != '\0'; i++) {
        if (!(my_isalpha(cmd_args[1][i])) && cmd_args[1][i] != '_') {
            write(2, "env: Variable name must contain"
                " alphanumeric characters.\n", 57);
            return false;
        }
    }
    return true;
}

bool is_set_command(sh_t *sh_st, exit_status_t *status)
{
    char **cmd_args = str_to_word_array(sh_st->command, " \n\t");
    bool is_correct_cmd = is_good_cmd("set", sh_st->command);
    int nb_ags = get_2d_arr_len(cmd_args);

    if (is_correct_cmd) {
        if (!error_nb_args(sh_st->envp, is_correct_cmd, nb_ags, cmd_args)) {
            *sh_st->error_code = 1;
            return true;
        }
        if (my_setenv(sh_st->envp, cmd_args[1], cmd_args[2], 1) == -1) {
            write(2, "Not enough space in the environment\n", 36);
            return true;
        }
        free_2d_array_of_char(cmd_args);
        *status = NORMAL;
        return true;
    } else {
        free_2d_array_of_char(cmd_args);
        return false;
    }
}
