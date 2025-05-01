/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** nothing
*/

#include <stdbool.h>
#include <unistd.h>
#include "mysh.h"
#include "commands.h"
#include "my_lib.h"

bool is_nothing(sh_t *sh_st, exit_status_t *status)
{
    char **command_element = str_to_word_array(sh_st->command, " \t\n");

    if (get_2d_arr_len(command_element) == 0) {
        *status = NOTHING;
        free_2d_array_of_char(command_element);
        return true;
    }
    free_2d_array_of_char(command_element);
    return false;
}
