/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** exit
*/

#include <unistd.h>
#include <stdbool.h>
#include <mysh.h>
#include "my_lib.h"
#include "utils.h"

bool is_exit_command(sh_t *sh_st, exit_status_t *status)
{
    if (my_strlen(sh_st->command) <= 1)
        return false;
    if (is_good_cmd("exit", sh_st->command)) {
        *status = EXIT;
        return true;
    }
    return false;
}
