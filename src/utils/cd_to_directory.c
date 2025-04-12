/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** cd_to_directory
*/

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "my_lib.h"

int check_variable_result(char *current_directory,
    int *error_code, int is_variable, char *path)
{
    if (!current_directory && is_variable) {
        write(2, "No $", 4);
        my_write_min(path, 2);
        write(2, " variable found\n", 16);
    }
    if (!current_directory) {
        *error_code = 84;
        return 0;
    }
    return 1;
}

int is_too_much_args(int nb_args, char **command_element, int *error_code)
{
    if (nb_args > 2) {
        *error_code = 84;
        write(2, "cd: Too many arguments.\n", 25);
        free_2d_array_of_char(command_element);
        return 1;
    }
    return 0;
}

void set_variable(char ***envp, char *current_directory,
    char *old_directory, int *error_code)
{
    char *directory = NULL;

    directory = getcwd(NULL, 0);
    my_setenv(envp, "OLDPWD", current_directory, 1);
    my_setenv(envp, "PWD", directory, 1);
    free(directory);
    my_free(current_directory, old_directory, NULL);
}

void cd_to_directory(char ***envp,
    char *path_to_directory, int *error_code, int is_variable)
{
    char *path = NULL;
    char *current_directory = get_environ_variable_value(envp, "PWD");
    char *old_directory = get_environ_variable_value(envp, "OLDPWD");
    char *directory = NULL;

    if (is_variable)
        path = get_environ_variable_value(envp, path_to_directory);
    else
        path = path_to_directory;
    if (!check_variable_result(current_directory, error_code,
        is_variable, path_to_directory))
        return;
    if (change_dir(path, current_directory, old_directory, error_code))
        return;
    set_variable(envp, current_directory, old_directory, error_code);
    if (is_variable)
        free(path);
}
