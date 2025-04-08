/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** get_exec
*/

#include "my_lib.h"

char *get_binary_name(char *command)
{
    char **command_element = str_to_word_array(command, " \n\t");
    char *command_name = my_strdup(command_element[0]);

    free_2d_array_of_char(command_element);
    return command_name;
}
