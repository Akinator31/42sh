/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_command
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_lib.h"
#include "mysh.h"
#include "utils.h"

int search_inhib(char *command)
{
    int i = 0;
    int nb_inib = 0;

    while (command[i] != '\0') {
        if (command[i] == INIBITHORS_CHAR)
            nb_inib++;
        i++;
    }
    return nb_inib;
}

static void free_all_array(char **arr1, char **arr2)
{
    free_2d_array_of_char(arr1);
    free_2d_array_of_char(arr2);
}

static int find_alias(char *command, alias_t *alias)
{
    int i = 0;
    int nb_alias = alias->nb_alias;
    char **command_array = str_to_word_array(command, " \t");
    char **alias_array = NULL;

    if (!command_array)
        return -1;
    while (i != nb_alias) {
        alias_array = str_to_word_array(alias[i].alias_name, " \t");
        if (!alias_array)
            return -1;
        if (strcmp(command_array[0], alias_array[0]) == 0) {
            free_all_array(command_array, alias_array);
            return i;
        }
        i++;
    }
    free_all_array(command_array, alias_array);
    return -1;
}

static char *set_real_command(char *command, config_rc_t *config,
    int alias_index)
{
    char *real_command = NULL;
    char **command_array = str_to_word_array(command, " \t");

    if (get_2d_arr_len(command_array) == 1) {
        free_2d_array_of_char(command_array);
        return config->alias[alias_index].command;
    }
    real_command = my_strcat_malloc(config->alias[alias_index].command,
        command + strlen(config->alias[alias_index].alias_name));
    return real_command;
}

static char **format_command(char *command, config_rc_t *config)
{
    int nb_inhib = 0;
    int alias_index = -1;
    char *real_command = command;

    if (config)
        alias_index = find_alias(command, config->alias);
    if (alias_index >= 0)
        real_command = set_real_command(command, config, alias_index);
    search_inhib(real_command);
    if (nb_inhib == 0)
        return str_to_word_array(real_command, " \n\t");
    if (nb_inhib % 2 != 0) {
        write(STDERR_FILENO, "Unmatched '''.\n", 15);
        return NULL;
    }
    return my_str_to_word_array_inhib(real_command, " \n\t", nb_inhib);
}

char **handle_command(sh_t *sh_st)
{
    char **command_array = format_command(sh_st->command, sh_st->config);

    handle_env_var_call(command_array, *sh_st->envp);
    return command_array;
}
