/*
** EPITECH PROJECT, 2025
** B-PSU-200-TLS-2-1-minishell1-pavel.de-wavrechin
** File description:
** get_binary
*/

#include <stdlib.h>
#include <fcntl.h>
#include "my_lib.h"
#include "utils.h"

char *is_file_executed(char *path, char *binary)
{
    int binary_path_size = my_strlen(path) + my_strlen(binary) + 3;
    char *binary_path = malloc(sizeof(char) *
        (my_strlen(path) + my_strlen(binary) + 3));

    my_memset(binary_path, '\0', binary_path_size);
    binary_path = my_strcat(binary_path, path);
    binary_path = my_strcat(binary_path, "/");
    binary_path = my_strcat(binary_path, binary);
    if (open(binary_path, O_EXCL) != -1)
        return binary_path;
    free(binary_path);
    return NULL;
}

char *get_binary_path(char **path_element, char *command)
{
    char *file_buffer = NULL;
    char **command_element = str_to_word_array(command, " \n\t");

    for (int i = 0; path_element[i]; i++) {
        file_buffer = is_file_executed(path_element[i], command_element[0]);
        if (file_buffer) {
            free_2d_array_of_char(command_element);
            return file_buffer;
        }
    }
    free_2d_array_of_char(command_element);
    return NULL;
}

char *get_binary(char ***envp, char *command)
{
    char *result = NULL;
    char *path = get_environ_variable_value(envp, "PATH");
    char **path_element = NULL;

    if (!path)
        return NULL;
    path_element = str_to_word_array(path, ":\n\t");
    result = get_binary_path(path_element, command);
    free_2d_array_of_char(path_element);
    free(path);
    return result;
}
