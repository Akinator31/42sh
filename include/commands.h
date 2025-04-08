/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** commands
*/

#ifndef INCLUDED_COMMANDS_H
    #define INCLUDED_COMMANDS_H
    #include <stdbool.h>
    #include "mysh.h"

bool is_exit_command(char ***envp, char *command,
    exit_status_t *status, int *error_code);
bool is_nothing(char ***envp, char *command,
    exit_status_t *status, int *error_code);
bool is_env_command(char ***envp, char *command,
    exit_status_t *status, int *error_code);
bool is_setenv_command(char ***envp, char *command,
    exit_status_t *status, int *error_code);
bool is_unsetenv_command(char ***envp, char *command,
    exit_status_t *status, int *error_code);
bool is_cd_command(char ***envp, char *command,
    exit_status_t *status, int *error_code);
void my_exec(char ***envp, char *command,
    exit_status_t *status, int *error_code);

#endif
