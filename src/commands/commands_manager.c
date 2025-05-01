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
#include "commands.h"
#include "mysh.h"
#include "utils.h"
#include "backtick.h"

static const my_builtins_t my_builtins_arr[] = {
    {"\n", &is_nothing},
    {"exit", &is_exit_command},
    {"env", &is_env_command},
    {"setenv", &is_setenv_command},
    {"unsetenv", &is_unsetenv_command},
    {"cd", &is_cd_command},
    {"history", &is_history_command},
    {"alias", &is_alias_command},
    {NULL, NULL},
};

static int handle_metacharacters(char *command, char ***envp, int *error_code,
    config_rc_t *config)
{
    if (handle_semicolons(command, envp, error_code, config))
        return 1;
    if (handle_double_right_redirection(command, error_code) == 0)
        return 1;
    if (handle_simple_right_redirection(command, error_code) == 0)
        return 1;
    if (handle_simple_left_redirection(command, error_code) == 0)
        return 1;
    if (handle_pipes(command, envp, error_code, config))
        return 1;
    return 0;
}

static void cleanup_processed_cmd(char *processed_cmd)
{
    if (processed_cmd)
        free(processed_cmd);
}

static exit_status_t check_builtins(sh_t *sh_st, exit_status_t *status)
{
    for (int i = 0; my_builtins_arr[i].builtins_name; i++)
        if (my_builtins_arr[i].f(sh_st, status))
            return *status;
    return 0;
}

exit_status_t analyse_command(char ***envp, char *command, int *error_code,
    config_rc_t *config)
{
    char *processed_cmd = NULL;
    exit_status_t status = NORMAL;
    sh_t sh_st = {envp, command, error_code, config};

    if (strchr(command, '`') != NULL) {
        processed_cmd = process_backticks(&sh_st);
        if (processed_cmd)
            sh_st.command = processed_cmd;
    }
    if (handle_metacharacters(command, envp, error_code, config)) {
        cleanup_processed_cmd(processed_cmd);
        return status;
    }
    if (check_builtins(&sh_st, &status)) {
        cleanup_processed_cmd(processed_cmd);
        return status;
    }
    my_exec(&sh_st, &status, 0);
    cleanup_processed_cmd(processed_cmd);
    return NORMAL;
}
