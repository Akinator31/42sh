/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** commands_manager
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_lib.h"
#include "commands.h"
#include "mysh.h"
#include "utils.h"

static const my_builtins_t my_builtins_arr[] = {
    {"\n", &is_nothing},
    {"exit", &is_exit_command},
    {"env", &is_env_command},
    {"setenv", &is_setenv_command},
    {"unsetenv", &is_unsetenv_command},
    {"cd", &is_cd_command},
    {NULL, NULL},
};

int handle_metacharacters(char *command, char ***envp, int *error_code)
{
    if (handle_semicolons(command, envp, error_code))
        return 1;
    handle_double_right_redirection(command);
    handle_simple_right_redirection(command);
    handle_simple_left_redirection(command);
    if (handle_pipes(command, envp, error_code))
        return 1;
    return 0;
}

exit_status_t analyse_command(char ***envp, char *command, int *error_code)
{
    exit_status_t status = NORMAL;

    if (handle_metacharacters(command, envp, error_code))
        return status;
    for (int i = 0; my_builtins_arr[i].builtins_name; i++)
        if (my_builtins_arr[i].f(envp, command, &status, error_code))
            return status;
    my_exec(envp, command, &status, error_code);
    return NORMAL;
}
