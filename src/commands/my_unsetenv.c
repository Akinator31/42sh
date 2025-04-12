/*
** EPITECH PROJECT, 2025
** minishell_1
** File description:
** unsetenv
*/

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_lib.h"
#include "utils.h"
#include "mysh.h"

bool check_variable_name(const char *name)
{
    int i = 0;

    while (name[i] != '\0') {
        if (name[i] == '=')
            return false;
        i++;
    }
    return true;
}

void replace_from_index(char **environ, int start, int end)
{
    int i = start;

    while (i <= end && environ[i]) {
        environ[i] = environ[i + 1];
        i++;
    }
}

int my_unsetenv(char **new_environ, const char *name)
{
    int i = 0;
    char **line_elements = NULL;
    int nb_vars = get_2d_arr_len(new_environ);

    if (!check_variable_name(name))
        return -1;
    while (new_environ[i]) {
        line_elements = str_to_word_array(new_environ[i], " =\n\t");
        if (my_strcmp(line_elements[0], name) == 0) {
            free(new_environ[i]);
            replace_from_index(new_environ, i, nb_vars);
            free_2d_array_of_char(line_elements);
            return 0;
        }
        free_2d_array_of_char(line_elements);
        i++;
    }
    return 0;
}

bool not_enough_args(bool is_correct_cmd, int nb_args,
    char **cmd_args, int *error_code)
{
    if (!is_correct_cmd) {
        free_2d_array_of_char(cmd_args);
        return false;
    }
    if (is_correct_cmd && nb_args == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        *error_code = 84;
        free_2d_array_of_char(cmd_args);
        return false;
    }
    return true;
}

bool is_unsetenv_command(char ***envp, char *command,
    exit_status_t *status, int *error_code)
{
    int i = 1;
    char **cmd_args = str_to_word_array(command, " \n\t");
    bool is_correct_cmd = is_good_cmd("unsetenv", command);
    int nb_args = get_2d_arr_len(cmd_args);
    char **new_environ = NULL;

    if (!not_enough_args(is_correct_cmd, nb_args, cmd_args, error_code))
        return false;
    while (is_correct_cmd && cmd_args[i]) {
        new_environ = duplicate_2d_char_array(*envp,
            get_2d_arr_len(*envp) + 1);
        my_unsetenv(new_environ, cmd_args[i]);
        *envp = new_environ;
        i++;
    }
    *status = NORMAL;
    free_2d_array_of_char(cmd_args);
    return true;
}
