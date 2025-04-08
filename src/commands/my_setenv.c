/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** setenv
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_lib.h"
#include "utils.h"
#include "mysh.h"

int env_var_already_exist(char ***envp, const char *variable)
{
    char **environ_elements = NULL;
    char **env = *envp;

    for (int i = 0; env[i]; i++) {
        environ_elements = str_to_word_array(env[i], " =\n\t");
        if (my_strcmp(environ_elements[0], variable) == 0) {
            free_2d_array_of_char(environ_elements);
            return i;
        }
        free_2d_array_of_char(environ_elements);
    }
    return -1;
}

int my_setenv(char ***envp, const char *name, const char *value,
    int overwrite)
{
    int environ_size = get_2d_arr_len(*envp);
    int variable_index_if_existing = env_var_already_exist(envp, name);
    char **new_environ = NULL;
    char **env = *envp;

    if (variable_index_if_existing != -1) {
        if (!overwrite)
            return 0;
        free(env[variable_index_if_existing]);
        env[variable_index_if_existing] = get_environ_var(name, value);
        return 0;
    } else {
        new_environ = duplicate_2d_char_array(*envp, environ_size + 2);
        free_2d_array_of_char(*envp);
        new_environ[environ_size] = get_environ_var(name, value);
        *envp = new_environ;
        return 0;
    }
}

static int incorrect_first_char(char **cmd_args)
{
    if (!(my_isalpha(cmd_args[1][0]) || cmd_args[1][0] == '_') ||
    (cmd_args[1][0] >= '0' && cmd_args[1][0] <= '9')) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return false;
    }
    return true;
}

bool error_nb_args(char ***envp, bool is_correct_cmd,
    int nb_args, char **cmd_args)
{
    if (is_correct_cmd && (nb_args > 3 || nb_args == 1)) {
        if (nb_args > 3)
            write(2, "setenv: Too many arguments.\n", 28);
        if (nb_args == 1)
            env(*envp);
        free_2d_array_of_char(cmd_args);
        return false;
    }
    if (!incorrect_first_char(cmd_args))
        return false;
    for (int i = 0; cmd_args[1][i] != '\0'; i++) {
        if (!(my_isalpha(cmd_args[1][i])) && cmd_args[1][i] != '_') {
            write(2, "setenv: Variable name must contain"
                " alphanumeric characters.\n", 60);
            return false;
        }
    }
    return true;
}

bool is_correct_arguments(char *name, char *value)
{
    int i = 0;

    if (!(my_isalpha(name[0]) || name[0] == '_')) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return false;
    }
    for (; name[i] != '\0'; i++) {
        if (!(my_isalpha(name[0])) && name[i] != '_') {
            write(2, "setenv: Variable name must contain"
                "alphanumeric characters.\n", 59);
            return false;
        }
    }
    return true;
}

bool is_setenv_command(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    char **cmd_args = str_to_word_array(command, " \n\t");
    bool is_correct_cmd = is_good_cmd("setenv", command);
    int nb_ags = get_2d_arr_len(cmd_args);

    if (is_correct_cmd) {
        if (!error_nb_args(envp, is_correct_cmd, nb_ags, cmd_args)) {
            *error_code = 1;
            return true;
        }
        if (my_setenv(envp, cmd_args[1], cmd_args[2], 1) == -1) {
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
