/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** check_meta_format
*/

#include <stdio.h>
#include "my_lib.h"

int check_meta_format(char *command, char *meta)
{
    char **array = str_to_word_array(command, " \n\t");
    int len = get_2d_arr_len(array);

    if (len == 1) {
        printf("Missing name for redirect.\n");
        free_2d_array_of_char(array);
        return 0;
    }
    if (len != 3) {
        printf("Invalid null command.\n");
        free_2d_array_of_char(array);
        return 0;
    }
    if (my_strcmp(array[1], meta) != 0) {
        printf("Missing name for redirect.\n");
        free_2d_array_of_char(array);
        return 0;
    }
    free_2d_array_of_char(array);
    return 1;
}
