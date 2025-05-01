/*
** EPITECH PROJECT, 2025
** B-PSU-200 : 42sh
** File description:
** commands
*/

#ifndef INCLUDED_COMMANDS_H
    #define INCLUDED_COMMANDS_H
    #include <stdbool.h>
    #include "mysh.h"

int handle_output_command(int result_command, char *buffer, char ***envp);

bool is_exit_command(sh_t *sh_st, exit_status_t *status);
bool is_nothing(sh_t *sh_st, exit_status_t *status);
bool is_env_command(sh_t *sh_st, exit_status_t *status);
bool is_setenv_command(sh_t *sh_st, exit_status_t *status);
bool is_unsetenv_command(sh_t *sh_st, exit_status_t *status);
bool is_cd_command(sh_t *sh_st, exit_status_t *status);
int my_exec(sh_t *sh_st, exit_status_t *status, int ret);
bool is_history_command(sh_t *sh_st, exit_status_t *status);
bool is_repeat_command(sh_t *sh_st, exit_status_t *status);

void my_write_history(char *line, char ***envp);

#endif
