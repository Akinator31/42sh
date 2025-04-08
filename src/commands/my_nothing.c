/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** nothing
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"
#include "commands.h"
#include "my_lib.h"
#include "utils.h"

bool is_nothing(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    if (my_strlen(command) == 1) {
        if (isatty(stdin->_fileno))
            print_prompt(*envp);
        *status = NOTHING;
        return true;
    }
    return false;
}
